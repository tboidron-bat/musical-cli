#include <musical/io/note/input/NoteLexer.h>
#include <cctype>

namespace musical::io::note
{

// ------------------------------------------------------------
// Normalisation à la volée (sans modifier la longueur)
// ------------------------------------------------------------
static unsigned char normalize_char(std::string_view input,
                                    size_t& i)
{
    unsigned char c =
        static_cast<unsigned char>(input[i]);

    // ASCII
    if (c < 0x80)
    {
        ++i;
        return static_cast<unsigned char>(std::tolower(c));
    }

    // UTF-8 2 bytes (accents latins)
    if ((c & 0xE0) == 0xC0 &&
        i + 1 < input.size())
    {
        unsigned char c2 =
            static_cast<unsigned char>(input[i + 1]);

        if (c == 0xC3)
        {
            i += 2;

            switch (c2)
            {
                case 0xA9: case 0xA8:
                case 0xAA: case 0xAB: return 'e'; // é è ê ë
                case 0xA0: case 0xA2:
                case 0xA4: return 'a';            // à â ä
                case 0xB9: case 0xBB:
                case 0xBC: return 'u';            // ù û ü
                case 0xAE: case 0xAF: return 'i'; // î ï
                case 0xB4: case 0xB6: return 'o'; // ô ö
                case 0xA7: return 'c';            // ç
            }
        }

        i += 2;
        return 0;
    }

    // UTF-8 3–4 bytes (♯ 𝄪 etc.)
    size_t len = 1;
    if ((c & 0xF0) == 0xE0)      len = 3;
    else if ((c & 0xF8) == 0xF0) len = 4;

    i += len;
    return 0;
}

static bool starts_with_ci(std::string_view input,
                           std::string_view prefix,
                           size_t& consumed_bytes)
{
    size_t i = 0;
    size_t j = 0;

    while (j < prefix.size())
    {
        if (i >= input.size())
            return false;

        size_t temp = i;
        unsigned char a =
            normalize_char(input, temp);

        unsigned char b =
            static_cast<unsigned char>(
                std::tolower(prefix[j])
            );

        if (a != b)
            return false;

        i = temp;
        ++j;
    }

    consumed_bytes = i;
    return true;
}


static bool starts_with_ci_ascii(std::string_view input,
                                 std::string_view prefix,
                                 size_t& consumed)
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

    consumed = prefix.size();
    return true;
}

static bool starts_with_exact(std::string_view input,
                              std::string_view prefix,
                              size_t& consumed)
{
    if (input.starts_with(prefix))
    {
        consumed = prefix.size();
        return true;
    }
    return false;
}



// ------------------------------------------------------------
// Parse longueur NOTE (NAME + ACCIDENTAL optionnel)
// ------------------------------------------------------------
size_t NoteLexer::parse_note_length(std::string_view input)
{
    size_t consumed = 0;

    // ------------------------------------------------------------
    // 1️⃣ NAME (accent + case insensitive)
    // ------------------------------------------------------------
    bool name_found = false;

    for (const auto& lex : lexemes)
    {
        if (lex.kind != TokenKind::NAME)
            continue;

        size_t bytes = 0;

        if (starts_with_ci(input, lex.text, bytes))
        {
            consumed = bytes;
            name_found = true;
            break;
        }
    }

    if (!name_found)
        return 0;

    // ------------------------------------------------------------
    // 2️⃣ ACCIDENTAL (ASCII CI OR Unicode exact)
    // ------------------------------------------------------------
    std::string_view rest = input.substr(consumed);

    for (const auto& lex : lexemes)
    {
        if (lex.kind != TokenKind::ACCIDENTAL)
            continue;

        size_t bytes = 0;

        // ASCII accidentals (#, b, bb, n, ##)
        bool is_ascii =
            lex.text.size() == 1
            ? static_cast<unsigned char>(lex.text[0]) < 0x80
            : true; // "bb", "##"

        if (is_ascii)
        {
            if (starts_with_ci_ascii(rest, lex.text, bytes))
            {
                consumed += bytes;
                break;
            }
        }
        else
        {
            // Unicode (♯ ♭ 𝄪 𝄫 ♮)
            if (starts_with_exact(rest, lex.text, bytes))
            {
                consumed += bytes;
                break;
            }
        }
    }

    return consumed;
}
// ------------------------------------------------------------
// Tokenize
// ------------------------------------------------------------
std::vector<token_t>
NoteLexer::tokenize(std::string_view input)
{
    std::vector<token_t> tokens;

    size_t offset = 0;

    while (offset < input.size())
    {
        bool matched = false;

        std::string_view remaining =
            input.substr(offset);

        for (const auto& lex : lexemes)
        {
            size_t bytes = 0;
            bool ok = false;

            if (lex.kind == TokenKind::NAME)
            {
                // UTF-8 accent + case insensitive
                ok = starts_with_ci(remaining,
                                    lex.text,
                                    bytes);
            }
            else // ACCIDENTAL
            {
                bool is_ascii =
                    lex.text.size() == 1
                    ? static_cast<unsigned char>(lex.text[0]) < 0x80
                    : true;

                if (is_ascii)
                {
                    ok = starts_with_ci_ascii(
                            remaining,
                            lex.text,
                            bytes);
                }
                else
                {
                    ok = starts_with_exact(
                            remaining,
                            lex.text,
                            bytes);
                }
            }

            if (ok)
            {
                tokens.push_back({
                    lex.kind,
                    input.substr(offset, bytes)
                });

                offset += bytes;
                matched = true;
                break;
            }
        }

        if (!matched)
            break;
    }

    return tokens;
}} // namespace musical::io::note