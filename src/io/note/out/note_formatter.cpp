#include <musical/io/note/out/note_formatter.h>

#include <musical/Core/pitch_t.h>

#include <map>
#include <stdexcept>
#include <array>
#include <cctype>

namespace musical::notation {
    constexpr char SHARP_ASCII = '#';
    constexpr char FLAT_ASCII  = 'b';
}

namespace musical::io::note::formatter
{    

// ------------------------------------------------------------
// NORMALISATION ASCII SIMPLE
// ------------------------------------------------------------
std::string normalize_name(const std::string& input)
{
    std::string result;
    result.reserve(input.size());

    for (unsigned char c : input)
        result += static_cast<char>(std::tolower(c));

    return result;
}


// ------------------------------------------------------------
// Latin → Saxon
// ------------------------------------------------------------
std::string to_saxon(const std::string& latin_name)
{
    static const std::map<std::string,char> fr_to_en = {
        { "do", 'c' },
        { "re", 'd' },
        { "mi", 'e' },
        { "fa", 'f' },
        { "sol",'g' },
        { "la", 'a' },
        { "si", 'b' }
    };

    std::string cleaned = normalize_name(latin_name);

    for (const auto& [fr, en] : fr_to_en)
    {
        if (cleaned.compare(0, fr.size(), fr) == 0)
        {
            cleaned.replace(0, fr.size(), std::string(1, en));
            break;
        }
    }

    return cleaned;
}


// ------------------------------------------------------------
// Saxon → Latin
// ------------------------------------------------------------
std::string to_latin(const std::string& name_en)
{
    static const std::map<char, std::string> en_to_fr = {
        { 'c', "do" },
        { 'd', "ré" },
        { 'e', "mi" },
        { 'f', "fa" },
        { 'g', "sol" },
        { 'a', "la" },
        { 'b', "si" }
    };    

    if (name_en.empty())
        throw std::invalid_argument(
            "[note::formatter::to_latin] empty string");

    std::string s = name_en;
    char first_char = static_cast<char>(std::tolower(s[0]));    

    auto it = en_to_fr.find(first_char);

    if (it != en_to_fr.end())
        s.replace(0, 1, it->second);
    else
        throw std::invalid_argument(
            "[note::formatter::to_latin] note not found");

    return s;    
}

} // namespace musical::io::note::formatter