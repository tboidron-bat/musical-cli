#include <musical/io/note/note_lexer.h>

#include <algorithm>
#include <cctype>

namespace musical::io::note
{

// ------------------------------------------------------------
// LEXER
// ------------------------------------------------------------
std::optional<token_t>
Lexer::parse(std::string_view input)
{
    if (input.empty())
        return std::nullopt;

    // Normalisation locale (majuscule autorisée)
    char letter = static_cast<char>(
        std::toupper(static_cast<unsigned char>(input.front()))
    );

    if (letter < 'A' || letter > 'G')
        return std::nullopt;

    int accidental = 0;
    std::size_t i = 1;

    while (i < input.size())
    {
        if (input[i] == '#')
            accidental++;
        else if (input[i] == 'b')
            accidental--;
        else
            break;

        ++i;
    }

    return token_t{
        letter,
        accidental,
        input.substr(0, i)
    };
}

// ------------------------------------------------------------
// NORMALISATION SIMPLE ASCII
// ------------------------------------------------------------
std::string normalize_name(const std::string& input)
{
    std::string result;
    result.reserve(input.size());

    for (unsigned char c : input)
    {
        result += static_cast<char>(std::tolower(c));
    }

    return result;
}

} // namespace musical::io::note
