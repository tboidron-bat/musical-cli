#include <musical/io/core/chord/parser/ChordParser.h>

#include <musical/core/chord/ChordType.h>
#include <musical/core/Pitch.h>
#include <musical/io/core/note/in/NoteLexer.h>
#include <musical/io/core/note/in/NoteParser.h>

#include <iostream>

//#define DEBUG

namespace musical::io::chord
{

using IT = musical::core::Interval;
using CT = musical::core::chord::ChordType;

// ------------------------------------------------------------
// Helpers
// ------------------------------------------------------------

static CT make_major()
{
    return CT({ IT::MAJOR_THIRD, IT::PERFECT_FIFTH });
}

static CT make_minor()
{
    return CT({ IT::MINOR_THIRD, IT::PERFECT_FIFTH });
}

static CT make_dim()
{
    return CT({ IT::MINOR_THIRD, IT::TRITONE });
}

static CT make_aug()
{
    return CT({ IT::MAJOR_THIRD, IT::MINOR_SIXTH });
}

// ------------------------------------------------------------
// ChordParser
// ------------------------------------------------------------

std::optional<core::chord::Chord>
ChordParser::parse(const std::vector<token_t>& tokens)
{

#ifdef DEBUG
    std::cout << "## class ChordParser ##\n";
#endif

    // --------------------------------------------------------
    // 1️⃣ ROOT
    // --------------------------------------------------------

    if (tokens.empty() || tokens[0].type != token_t::TokenType::ROOT)
        return std::nullopt;

    const auto& root_text =
        std::get<root_token_t>(tokens[0].value).text;

    auto note_tokens =
        musical::io::note::NoteLexer::tokenize(root_text);

    auto note_opt =
        musical::io::note::NoteParser::parse(note_tokens);

    if (!note_opt)
        return std::nullopt;

    musical::core::Pitch root_pitch = note_opt->to_pitch();

    // --------------------------------------------------------
    // 2️⃣ Default triad = major
    // --------------------------------------------------------

    CT chord_type = make_major();

    // --------------------------------------------------------
    // 3️⃣ Process LEXEMES
    // --------------------------------------------------------

    for (size_t i = 1; i < tokens.size(); ++i)
    {
        const auto& t = tokens[i];

        if (t.type == token_t::TokenType::SLASH)
            continue;

        if (t.type != token_t::TokenType::LEXEME)
            continue;

        const auto& lex =
            std::get<lexeme_token_t>(t.value);

        switch (lex.category)
        {
            case lexeme_t::Category::TRIAD:
            {
                if (lex.text == "m" || lex.text == "min" || lex.text == "-")
                    chord_type = make_minor();

                else if (lex.text == "dim")
                    chord_type = make_dim();

                else if (lex.text == "aug")
                    chord_type = make_aug();

                break;
            }

            case lexeme_t::Category::SEVENTH:
            {
                if (lex.text == "7")
                    chord_type += IT::MINOR_SEVENTH;
                else
                    chord_type += IT::MAJOR_SEVENTH;

                break;
            }

            case lexeme_t::Category::EXTENSION:
            {
                if (lex.text == "9")
                    chord_type += IT::MAJOR_NINTH;

                else if (lex.text == "11")
                    chord_type += IT::PERFECT_ELEVENTH;

                else if (lex.text == "13")
                    chord_type += IT::MAJOR_THIRTEENTH;

                break;
            }

            case lexeme_t::Category::ALTERATION:
            {
                if (lex.text == "b5")
                {
                    chord_type -= IT::PERFECT_FIFTH;
                    chord_type += IT::TRITONE;
                }

                break;
            }

            case lexeme_t::Category::SUSPENSION:
            {
                // remove 3rd
                chord_type -= IT::MAJOR_THIRD;
                chord_type -= IT::MINOR_THIRD;

                if (lex.text == "sus2")
                    chord_type += IT::MAJOR_SECOND;

                else if (lex.text == "sus4")
                    chord_type += IT::PERFECT_FOURTH;

                break;
            }

            case lexeme_t::Category::ADDITION:
            {
                if (lex.text == "add9")
                    chord_type += IT::MAJOR_NINTH;

                else if (lex.text == "add11")
                    chord_type += IT::PERFECT_ELEVENTH;

                break;
            }

            case lexeme_t::Category::SPECIAL:
            {
                return std::nullopt;
            }
        }
    }

    if (chord_type.empty())
    {
        std::cerr << "Chord parsing failed\n";
        return std::nullopt;
    }

    // --------------------------------------------------------
    // 4️⃣ Build chord
    // --------------------------------------------------------

    return musical::core::chord::Chord(
        root_pitch,
        chord_type
    );
}

} // namespace musical::io::chord