#include <musical/io/utils/input/normalize_to_ascii.h>
#include <cctype>

namespace musical::io
{

std::string
normalize_to_ascii(std::string_view input)
{
    std::string out;

    for (size_t i = 0; i < input.size();)
    {
        unsigned char c =
            static_cast<unsigned char>(input[i]);

        // ----------------------------------------------------
        // ASCII
        // ----------------------------------------------------
        if (c < 0x80)
        {
            out += static_cast<char>(c);
            ++i;
            continue;
        }

        // ----------------------------------------------------
        // UTF-8 2 bytes (accents latins)
        // ----------------------------------------------------
        if ((c & 0xE0) == 0xC0 &&
            i + 1 < input.size())
        {
            unsigned char c2 =
                static_cast<unsigned char>(input[i + 1]);

            if (c == 0xC3)
            {
                switch (c2)
                {
                    case 0xA9: case 0xA8:
                    case 0xAA: case 0xAB: out += 'e'; break;
                    case 0xA0: case 0xA2:
                    case 0xA4: out += 'a'; break;
                    case 0xB9: case 0xBB:
                    case 0xBC: out += 'u'; break;
                    case 0xAE: case 0xAF: out += 'i'; break;
                    case 0xB4: case 0xB6: out += 'o'; break;
                    case 0x87: out += 'C'; break;                    
                    case 0xA7: out += 'c'; break;
                }
            }

            i += 2;
            continue;
        }

        // ----------------------------------------------------
        // UTF-8 3 bytes (♯ ♭ ♮)
        // ----------------------------------------------------
        if ((c & 0xF0) == 0xE0 &&
            i + 2 < input.size())
        {
            auto sym = input.substr(i, 3);

            if (sym == "♯") out += '#';
            else if (sym == "♭") out += 'b';
            else if (sym == "♮")
            {
                // ignoré
            }

            i += 3;
            continue;
        }

        // ----------------------------------------------------
        // UTF-8 4 bytes (𝄪 𝄫)
        // ----------------------------------------------------
        if ((c & 0xF8) == 0xF0 &&
            i + 3 < input.size())
        {
            auto sym = input.substr(i, 4);

            if (sym == "𝄪") out += "##";
            else if (sym == "𝄫") out += "bb";

            i += 4;
            continue;
        }

        ++i;
    }

    return out;
}

}