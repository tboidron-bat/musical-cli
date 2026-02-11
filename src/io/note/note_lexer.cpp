#include <musical/io/note/note_lexer.h>

#include <map>

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

std::string normalize_name(const std::string& input)
{
    static const std::map<wchar_t, wchar_t> accent_map = {
        { L'é', L'e' },
        { L'É', L'e' },
        { L'è', L'e' },
        { L'à', L'a' },
        { L'â', L'a' },
        { L'ê', L'e' },
        { L'î', L'i' },
        // ajoute d'autres si besoin
    };

    // UTF-8 -> wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(input);

    std::wstring normalized;
    for (wchar_t wc : wstr) {
        auto it = accent_map.find(wc);
        if (it != accent_map.end())
            normalized += it->second;
        else
            normalized += std::towlower(wc);
    }

    // wstring -> UTF-8
    return converter.to_bytes(normalized);
}


}
