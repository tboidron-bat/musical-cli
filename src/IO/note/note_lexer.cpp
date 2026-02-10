#include <musical/IO/note/note_lexer.h>

namespace musical::io::note
{

std::optional<token_t>
Lexer::parse(std::string_view input)
{
    if (input.empty())
        return std::nullopt;

    char letter = input.front();

    if (letter < 'A' || letter > 'G')
        return std::nullopt;

    int accidental = 0;
    size_t i = 1;

    while (i < input.size())
    {
        if (input[i] == '#')
        {
            accidental++;
        }
        else if (input[i] == 'b')
        {
            accidental--;
        }
        else
        {
            break;
        }

        ++i;
    }

    return token_t{
        letter,
        accidental,
        input.substr(0, i)
    };
}

}
