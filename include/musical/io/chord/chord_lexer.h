#pragma once

#include <string>
#include <vector>
#include <optional>

namespace musical::chord
{
    enum class TokenKind
    {
        QUALITY,
        EXTENSION,
        ALTERATION,
        SUSPENSION,
        ADD,
        UNKNOWN
    };

    struct token_t
    {
        std::string _lexeme;      // texte original
        std::string _canonical;   // forme normalisée
        TokenKind   _kind;
    };

    class Lexer
    {
    public:
        static std::vector<token_t> tokenize(const std::string& input);

    private:
        static std::optional<token_t> match_token(std::string_view input);
    };
}
