#include <musical/io/chord/tokens.h>

#include <vector>
#include <optional>

namespace musical::io::chord
{

// -------------------------------------------------------------
// ROOT = [A-G][#|b]?
// -------------------------------------------------------------
static std::optional<std::string>
match_root(std::string_view input)
{
    if (input.empty())
        return std::nullopt;

    char c = input[0];

    if (c < 'A' || c > 'G')
        return std::nullopt;

    if (input.size() >= 2)
    {
        char accidental = input[1];
        if (accidental == '#' || accidental == 'b')
            return std::string(input.substr(0, 2));
    }

    return std::string(input.substr(0, 1));
}

// -------------------------------------------------------------
// Lexeme match (constexpr table triée)
// -------------------------------------------------------------
static std::optional<Lexeme>
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
std::vector<Token> tokenize(std::string_view input)
{
    std::vector<Token> tokens;

    while (!input.empty())
    {
        // Slash
        if (input.front() == '/')
        {
            tokens.push_back({TokenType::SLASH, RootToken{"/"}});
            input.remove_prefix(1);
            continue;
        }

        // Root
        if (auto root = match_root(input))
        {
            tokens.push_back({
                TokenType::ROOT,
                RootToken{*root}
            });

            input.remove_prefix(root->size());
            continue;
        }

        // Lexeme
        if (auto lex = match_lexeme(input))
        {
            tokens.push_back({
                TokenType::LEXEME,
                LexemeToken{lex->category, std::string(lex->text)}
            });

            input.remove_prefix(lex->text.size());
            continue;
        }

        // Unknown
        tokens.push_back({
            TokenType::UNKNOWN,
            RootToken{std::string(1, input.front())}
        });

        input.remove_prefix(1);
    }

    return tokens;
}

}
