#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <variant>

#include <musical/io/chord/input/lexemes.h>

namespace musical::io::chord
{

struct root_token_t
{
    std::string text;
};

struct lexeme_token_t
{
    lexeme_t::Category category;
    std::string text;
};

struct token_t
{
    enum class TokenType
    {
        ROOT,
        LEXEME,
        SLASH,
        UNKNOWN
    };


    TokenType type;
    std::variant<root_token_t, lexeme_token_t> value;
};

class ChordLexer
{
public:

    /**
     * @brief Tokenize une chaîne d'accord.
     *
     * L'entrée peut être en UTF-8 (♯, ♭, accents, etc.).
     * Elle sera normalisée avant analyse.
     *
     * @param input Chaîne d'entrée (ex: "Cmaj7")
     * @return Liste des tokens détectés
     */
    static std::vector<token_t> tokenize(std::string_view input);
};

} // namespace musical::io::chord