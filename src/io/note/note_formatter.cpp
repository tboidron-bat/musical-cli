#include <musical/io/note/note_formatter.h>
#include <musical/io/note/note_lexer.h>

#include <map>
#include <stdexcept>
#include <array>
#include <cctype>

namespace musical::io::note::formatter
{    

std::string to_string(const core::Note& note) 
{
    static constexpr std::array<char,7> letters =
        { 'c','d','e','f','g','a','b' };

    char letter = letters[static_cast<int>(note.name())];

    std::string s(1, letter);


    switch(note.accidental()) {
        case musical::core::Note::Accidental::SHARP:
            s += musical::notation::SHARP_ASCII; 
            break;
        case musical::core::Note::Accidental::FLAT:
            s += musical::notation::FLAT_ASCII; 
            break;
        case musical::core::Note::Accidental::DOUBLE_SHARP:
            s += std::string(2, musical::notation::SHARP_ASCII);
            break;
        case musical::core::Note::Accidental::DOUBLE_FLAT:
            s += std::string(2, musical::notation::FLAT_ASCII);
            break;
        case musical::core::Note::Accidental::NONE:
        default:
            break;
    }
    return s;
}

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

    std::string cleaned = 
        musical::io::note::normalize_name(latin_name);

    //std::cout << "[NoteService]\\(to_saxon)"    << "cleaned=" << cleaned      << std::endl;

    for (const auto& [fr, en] : fr_to_en) {
        if (cleaned.compare(0, fr.size(), fr) == 0) {
            cleaned.replace(0, fr.size(), std::string(1, en));
            break;
        }
    }

    return cleaned;
}
std::string to_latin(const std::string&name_en)
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

    if (name_en.empty()) {
        throw std::invalid_argument(
            "[musical::NoteService]\\to_latin(..) empty string");    
    }

    std::string s = name_en;
    char first_char = static_cast<char>(std::tolower(s[0]));    

    auto it = en_to_fr.find(first_char);
    if (it != en_to_fr.end()) {
        s.replace(0, 1, it->second);
    }
    else{
        throw std::invalid_argument(
            "[musical::NoteService]\\to_latin(..) note not found");    
    }
    return s;    
}

}