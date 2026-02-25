#include <musical/io/chord/input/Lexer.h>
#include <musical/io/chord/input/tokens.h>
#include <musical/io/note/input/Lexer.h>

#include <vector>
#include <optional>
#include <cctype>

namespace musical::io::chord
{

// -------------------------------------------------------------
// ASCII case-insensitive comparison
// -------------------------------------------------------------
static bool starts_with_ci_ascii(std::string_view input,
                                 std::string_view prefix)
{
    if (input.size() < prefix.size())
        return false;

    for (size_t i = 0; i < prefix.size(); ++i)
    {
        unsigned char a =
            static_cast<unsigned char>(input[i]);

        unsigned char b =
            static_cast<unsigned char>(prefix[i]);

        if (std::tolower(a) != std::tolower(b))
            return false;
    }

    return true;
}

// -------------------------------------------------------------
// Lexeme match (table triée par longueur décroissante)
// -------------------------------------------------------------
static std::optional<Lexeme>
match_lexeme(std::string_view input)
{
    for (const auto& lex : SORTED_LEXEMES)
    {
        bool match = false;

        if (lex.case_sensitive)
        {
            match = input.starts_with(lex.text);
        }
        else
        {
            match = starts_with_ci_ascii(input, lex.text);
        }

        if (match)
            return lex;
    }

    return std::nullopt;
}

// -------------------------------------------------------------
// Tokenize
// -------------------------------------------------------------
std::vector<Token>
Lexer::tokenize(std::string_view input)
{
    std::vector<Token> tokens;

    while (!input.empty())
    {
        // -------------------------------------------------
        // Slash (bass note indicator)
        // -------------------------------------------------
        if (input.front() == '/')
        {
            tokens.push_back({
                TokenType::SLASH,
                RootToken{"/"}
            });

            input.remove_prefix(1);
            continue;
        }

        // -------------------------------------------------
        // Root (uniquement au début ou après slash)
        // -------------------------------------------------
        bool expect_root =
            tokens.empty() ||
            tokens.back().type == TokenType::SLASH;

        if (expect_root)
        {
            size_t consumed =
                musical::io::note::Lexer::parse_note_length(input);

            if (consumed > 0)
            {
                tokens.push_back({
                    TokenType::ROOT,
                    RootToken{
                        std::string(input.substr(0, consumed))
                    }
                });

                input.remove_prefix(consumed);
                continue;
            }
        }

        // -------------------------------------------------
        // Lexeme chord (maj7, min, sus2, add11, etc.)
        // -------------------------------------------------
        if (auto lex = match_lexeme(input))
        {
            tokens.push_back({
                TokenType::LEXEME,
                LexemeToken{
                    lex->category,
                    std::string(lex->text)
                }
            });

            input.remove_prefix(lex->text.size());
            continue;
        }

        // -------------------------------------------------
        // Unknown character
        // -------------------------------------------------
        tokens.push_back({
            TokenType::UNKNOWN,
            RootToken{
                std::string(1, input.front())
            }
        });

        input.remove_prefix(1);
    }

    return tokens;
}

} // namespace musical::io::chord