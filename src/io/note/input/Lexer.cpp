#include <musical/io/note/input/Lexer.h>

#include <algorithm>
#include <cctype>
#include <string>

namespace musical::io::note
{

namespace
{
    // Normalisation minimale :
    // - ASCII → lowercase
    // - UTF-8 "é" → 'e'
    std::string normalize(std::string_view input)
    {
        std::string result;
        result.reserve(input.size());

        for (std::size_t i = 0; i < input.size(); )
        {
            unsigned char c = static_cast<unsigned char>(input[i]);

            // ASCII
            if (c < 128)
            {
                result.push_back(
                    static_cast<char>(std::tolower(c))
                );
                ++i;
            }
            // UTF-8 "é" (0xC3 0xA9)
            else if (i + 1 < input.size() &&
                     static_cast<unsigned char>(input[i]) == 0xC3 &&
                     static_cast<unsigned char>(input[i + 1]) == 0xA9)
            {
                result.push_back('e');
                i += 2;
            }
            else
            {
                // copie brute pour ♯ ♭ 𝄪 𝄫 etc.
                result.push_back(input[i]);
                ++i;
            }
        }

        return result;
    }
}


std::optional<std::vector<token_t>>
Lexer::tokenize(std::string_view input)
{
    // 1️⃣ Normalisation
    std::string normalized = normalize(input);
    std::string_view view(normalized);

    // 2️⃣ Copie triée par longueur décroissante
    std::array<lexeme_t, lexemes.size()> sorted = lexemes;

    std::sort(sorted.begin(), sorted.end(),
        [](const lexeme_t& a, const lexeme_t& b)
        {
            return a._text.size() > b._text.size();
        });

    std::vector<token_t> tokens;

    // 3️⃣ Scan déterministe
    while (!view.empty())
    {
        bool matched = false;

        for (const auto& lex : sorted)
        {
            if (view.starts_with(lex._text))
            {
                tokens.push_back(token_t{
                    lex._kind,
                    view.substr(0, lex._text.size())
                });

                view.remove_prefix(lex._text.size());
                matched = true;
                break;
            }
        }

        if (!matched)
            return std::nullopt;
    }

    return tokens;
}

}
