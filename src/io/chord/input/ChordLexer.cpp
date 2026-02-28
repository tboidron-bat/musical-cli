#include <musical/io/chord/input/ChordLexer.h>
#include <musical/io/note/input/NoteLexer.h>
#include <musical/io/utils/input/normalize_to_ascii.h>

#include <vector>
#include <optional>

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

    return tokens;
}

} // namespace musical::io::chord