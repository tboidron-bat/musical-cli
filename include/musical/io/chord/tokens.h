#pragma once

#include <string>
#include <variant>
#include <optional>
#include <vector>

#include <musical/io/chord/lexemes_defs.h>

namespace musical::io::chord
{

enum class TokenType
{
    ROOT,
    LEXEME,
    SLASH,
    UNKNOWN
};

struct RootToken
{
    std::string text;
};

struct LexemeToken
{
    LexemeCategory category;
    std::string text;
};

struct Token
{
    TokenType type;
    std::variant<RootToken, LexemeToken> value;
};

std::vector<Token> tokenize(std::string_view input);

}
