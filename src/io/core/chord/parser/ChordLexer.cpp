#include <musical/io/core/chord/parser/ChordLexer.h>
#include <musical/io/core/note/in/NoteLexer.h>
#include <musical/io/utils/in/normalize_to_ascii.h>

#include <vector>
#include <optional>
#include <iostream>

//#define DEBUG

namespace musical::io::chord
{

// -------------------------------------------------------------
// Lexeme match (table triée par longueur décroissante)
// -------------------------------------------------------------
static std::optional<lexeme_t>
match_lexeme(std::string_view input)
{
    for (const auto& lex : SORTED_LEXEMES)
    {
        if (input.starts_with(lex.text))
            return lex;
    }

    return std::nullopt;
}

// -------------------------------------------------------------
// Tokenize
// -------------------------------------------------------------
std::vector<token_t>
ChordLexer::tokenize(std::string_view input)
{
    std::vector<token_t> tokens;

    // 🔹 Normalisation globale une seule fois
    std::string normalized =
        musical::io::normalize_to_ascii(input);

    std::string_view view = normalized;

    while (!view.empty())
    {
// #ifdef DEBUG
//     std::cerr << "Remaining: [" << view << "]\n";
// #endif

        // -------------------------------------------------
        // Slash (bass note indicator)
        // -------------------------------------------------
        if (view.front() == '/')
        {
            tokens.push_back({
                token_t::TokenType::SLASH,
                root_token_t{"/"}
            });

            view.remove_prefix(1);
            continue;
        }

        // -------------------------------------------------
        // Root (début ou après slash)
        // -------------------------------------------------
        bool expect_root =
            tokens.empty() ||
            tokens.back().type == token_t::TokenType::SLASH;

        if (expect_root)
        {
            size_t consumed =
                musical::io::note::NoteLexer::parse_note_length(view);

            if (consumed > 0)
            {
                std::string root =
                    std::string(view.substr(0, consumed));

                tokens.push_back({
                    token_t::TokenType::ROOT,
                    root_token_t{ root }
                });

// #ifdef DEBUG                
//     std::cerr << "[ChordLexer::]" << __func__ << std::endl; 
// #endif

                view.remove_prefix(consumed);
                continue;
            }
        }

        // -------------------------------------------------
        // Lexeme chord (maj7, min, sus2, add11, etc.)
        // -------------------------------------------------
        if (auto lex = match_lexeme(view))
        {
            tokens.push_back({
                token_t::TokenType::LEXEME,
                lexeme_token_t{
                    lex->category,
                    std::string(lex->text)
                }
            });

            view.remove_prefix(lex->text.size());
            continue;
        }

        // -------------------------------------------------
        // Unknown character
        // -------------------------------------------------
        tokens.push_back({
            token_t::TokenType::UNKNOWN,
            root_token_t{
                std::string(1, view.front())
            }
        });

        view.remove_prefix(1);
    }

#ifdef DEBUG
    std::cout << "\nDEBUG:\n#-class ChordLexer-#\ncalling:" << __func__ << "(" << input << ")" << "\n";
    for (const auto& t : tokens)
        std::cerr << t << "\n";
    //std::cerr << "\n";
#endif    

    return tokens;
}
std::ostream& operator<<(std::ostream& os, const token_t& tok)
{
    using TT = token_t::TokenType;

    switch (tok.type)
    {
        case TT::ROOT:
        {
            const auto& v = std::get<root_token_t>(tok.value);
            return os << "[ROOT]=(" << v.text << ")";
        }

        case TT::LEXEME:
        {
            const auto& v = std::get<lexeme_token_t>(tok.value);
            return os << "[" << v.category
                      << "]=(" << v.text << ")";
        }

        case TT::SLASH:
            return os << "SLASH=[/]";

        case TT::UNKNOWN:
        {
            const auto& v = std::get<root_token_t>(tok.value);
            return os << "UNKNOWN=[" << v.text << "]";
        }    
    }

    return os;
}
} // namespace musical::io::chord