#include <musical/io/chord/input/ChordParser.h>

#include <musical/Core/chord/ChordType.h>
#include <musical/Core/pitch_t.h>
#include <musical/io/note/input/NoteLexer.h>
#include <musical/io/note/input/NoteParser.h>
#include <musical/io/chord/output/stream.h>

#include <algorithm>
#include <iostream>

//#define CHORD_PARSER_DEBUG

namespace musical::io::chord
{

using IT = musical::core::IntervalType;

// ------------------------------------------------------------
// Helpers
// ------------------------------------------------------------

static void make_major(std::vector<IT>& iv)
{
    iv = { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE };
}

static void make_minor(std::vector<IT>& iv)
{
    iv = { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE };
}

static void make_dim(std::vector<IT>& iv)
{
    iv = { IT::TIERCE_MINEURE, IT::TRITON };
}

static void make_aug(std::vector<IT>& iv)
{
    iv = { IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE };
}

// ------------------------------------------------------------
// ChordParser
// ------------------------------------------------------------

std::optional<core::chord::Chord>
ChordParser::parse(const std::vector<token_t>& tokens)
{

#ifdef CHORD_PARSER_DEBUG    

    std::cout << "\n#DEBUG ChordParser::parse(...) Tokens:\n";

    for (const auto& t : tokens)
    {
        switch (t.type)
        {
            case token_t::TokenType::ROOT:
                std::cout << "  ROOT: "
                          << std::get<root_token_t>(t.value).text
                          << "\n";
                break;

            case token_t::TokenType::LEXEME:
            {
                const auto& lex =
                    std::get<lexeme_token_t>(t.value);

                std::cout << "  LEXEME: "
                          << lex.text
                          << " ("
                          << lex.category
                          << ")\n";
                break;
            }

            case token_t::TokenType::SLASH:
                std::cout << "  SLASH\n";
                break;

            case token_t::TokenType::UNKNOWN:
                std::cout << "  UNKNOWN\n";
                break;
        }
    }
#endif

    // --------------------------------------------------------
    // 1️⃣ ROOT
    // --------------------------------------------------------

    if (tokens[0].type != token_t::TokenType::ROOT)
        return std::nullopt;

    const auto& root_text =
        std::get<root_token_t>(tokens[0].value).text;

    auto note_tokens =
        musical::io::note::NoteLexer::tokenize(root_text);

    auto pitch_opt =
        musical::io::note::NoteParser::parse(note_tokens);

    if (!pitch_opt)
        return std::nullopt;

    musical::core::pitch_t root_pitch = *pitch_opt;

    // --------------------------------------------------------
    // 2️⃣ Default triad = major
    // --------------------------------------------------------

    std::vector<IT> intervals;
    make_major(intervals);

    // --------------------------------------------------------
    // 3️⃣ Process LEXEMES
    // --------------------------------------------------------

    for (size_t i = 1; i < tokens.size(); ++i)
    {
        const auto& t = tokens[i];

        if (t.type == token_t::TokenType::SLASH)
            continue; // basse alternative à gérer plus tard

        if (t.type != token_t::TokenType::LEXEME)
            continue;

        const auto& lex =
            std::get<lexeme_token_t>(t.value);

        switch (lex.category)
        {
            case lexeme_t::Category::TRIAD:
            {
                if (lex.text == "m" ||
                    lex.text == "min" ||
                    lex.text == "-")
                {
                    make_minor(intervals);
                }
                else if (lex.text == "dim")
                {
                    make_dim(intervals);
                }
                else if (lex.text == "aug")
                {
                    make_aug(intervals);
                }
                break;
            }

            case lexeme_t::Category::SEVENTH:
            {
                if (lex.text == "7")
                    intervals.push_back(IT::SEPTIEME_MINEURE);
                else
                    intervals.push_back(IT::SEPTIEME_MAJEURE);
                break;
            }

            case lexeme_t::Category::EXTENSION:
            {
                if (lex.text == "9")
                    intervals.push_back(IT::NEUVIEME_MAJEURE);
                else if (lex.text == "11")
                    intervals.push_back(IT::ONZIEME);
                else if (lex.text == "13")
                    intervals.push_back(IT::TREIZIEME_MAJEURE);
                break;
            }

            case lexeme_t::Category::ALTERATION:
            {
                if (lex.text == "b5")
                {
                    auto it = std::find(intervals.begin(),
                                        intervals.end(),
                                        IT::QUINTE_JUSTE);

                    if (it != intervals.end())
                        *it = IT::TRITON;
                }
                break;
            }

            case lexeme_t::Category::SUSPENSION:
            {
                // supprimer tierce
                intervals.erase(
                    std::remove_if(intervals.begin(),
                                   intervals.end(),
                                   [](IT iv)
                                   {
                                       return iv == IT::TIERCE_MAJEURE ||
                                              iv == IT::TIERCE_MINEURE;
                                   }),
                    intervals.end()
                );

                if (lex.text == "sus2")
                    intervals.push_back(IT::SECONDE_MAJEURE);
                else if (lex.text == "sus4")
                    intervals.push_back(IT::QUARTE_JUSTE);

                break;
            }

            case lexeme_t::Category::ADDITION:
            {
                if (lex.text == "add9")
                    intervals.push_back(IT::NEUVIEME_MAJEURE);
                else if (lex.text == "add11")
                    intervals.push_back(IT::ONZIEME);
                break;
            }

            case lexeme_t::Category::SPECIAL:
            {
                return std::nullopt;
            }
        }
    }

    if(intervals.empty())
    {
        std::cerr << "Chord parsing failed\n";
        return std::nullopt;
    }


    // --------------------------------------------------------
    // 4️⃣ Normalisation
    // --------------------------------------------------------

    std::sort(intervals.begin(), intervals.end());

    return musical::core::chord::Chord(
        root_pitch,
        musical::core::chord::ChordType(intervals)
    );
}

} // namespace musical::io::chord