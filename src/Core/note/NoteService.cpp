#include <musical/Core/note/NoteService.h>

#include <musical/Core/note/NoteFactory.h>

#include <map>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <codecvt>
#include <locale>

using namespace musical;

std::string NoteService::to_string(const Note& note) 
{
    std::string s(1, note.GetPitch()._name);

    switch(note.GetPitch()._accid) {
        case musical::Accidental::SHARP:
            s += SHARP_CHAR; 
            break;
        case musical::Accidental::FLAT:
            s += FLAT_CHAR; 
            break;
        case musical::Accidental::DOUBLE_SHARP:
            s += std::string(2, SHARP_CHAR);
            break;
        case musical::Accidental::DOUBLE_FLAT:
            s += std::string(2, FLAT_CHAR);
            break;
        case musical::Accidental::NONE:
        default:
            break;
    }
    return s;
}

std::array<std::string,12> NoteService::all_with_flat()
{
    constexpr char FLAT_CHAR = 'b';   

    static const std::array<char, 7> SAXON_NAMES =  
        { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };


    static std::array<std::string,12> array = {};

    if(array[0].empty())
    {
        auto it = array.begin();

        for(char n : SAXON_NAMES)
        {
            *it = std::string(1,n);         // note naturelle
            ++it;

            if(n == 'f' || n == 'c')
                continue;

            *it = std::string(1,n) + FLAT_CHAR;   // note bémol       
            ++it;
        }
    }
    return array;
}
std::array<std::string,12> NoteService::all_with_sharp()
{
    constexpr char SHARP_CHAR = '#';      

    static const std::array<char, 7> SAXON_NAMES =  
        { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };


    static std::array<std::string,12> array = {};

    if(array[0].empty())
    {
        auto it = array.begin();

        for(char n : SAXON_NAMES)
        {
            *it = std::string(1,n);         // note naturelle
            ++it;

            if(n == 'b' || n == 'e')
                continue;

            *it = std::string(1,n) + SHARP_CHAR;   // note dièse       
            ++it;
        }
    }
    return array;
}
std::string NoteService::normalize_note_name(const std::string& input)
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

std::size_t NoteService::chromatic_index(const Note&note) 
{
    // Table de correspondance des noms de base (sans altération)
    // basé sur l'ordre : C=0, C#=1, D=2, ..., B=11
    static const std::map<char, int> base_values = {
        { 'c', 0 },
        { 'd', 2 },
        { 'e', 4 },
        { 'f', 5 },
        { 'g', 7 },
        { 'a', 9 },
        { 'b', 11 }
    };

    int base = base_values.at(std::tolower(note.GetPitch()._name)); // nom de note
    int offset = 0;

    switch (note.GetPitch()._accid) {
        case musical::Accidental::SHARP:        offset = 1; break;
        case musical::Accidental::FLAT:         offset = -1; break;
        case musical::Accidental::DOUBLE_SHARP: offset = 2; break;
        case musical::Accidental::DOUBLE_FLAT:  offset = -2; break;
        default: break;
    }

    return (base + offset + 12) % 12;
}


size_t musical::NoteService::find(const musical::Note& note)
{
    using Acc = musical::Accidental;

    const auto& chromatic_set = 
        (note.GetPitch()._accid == Acc::NONE || note.GetPitch()._accid == Acc::SHARP)
        ? all_with_sharp()
        : all_with_flat();

    auto it = std::find(chromatic_set.begin(), chromatic_set.end(), musical::NoteService::to_string(note));

    if (it == chromatic_set.end())
        throw std::runtime_error("[find] Note not found in chromatic set: " + musical::NoteService::to_string(note));

    return std::distance(chromatic_set.begin(), it);
}
std::string NoteService::to_saxon(const std::string& latin_name)
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

    std::string cleaned = normalize_note_name(latin_name);

    //std::cout << "[NoteService]\\(to_saxon)"    << "cleaned=" << cleaned      << std::endl;

    for (const auto& [fr, en] : fr_to_en) {
        if (cleaned.compare(0, fr.size(), fr) == 0) {
            cleaned.replace(0, fr.size(), std::string(1, en));
            break;
        }
    }

    return cleaned;
}
std::string musical::NoteService::to_latin(const std::string&name_en)
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


    //std::cout << "[musical::NoteService]\\(to_latin)" << "s=" << s  << std::endl;    

    return s;
}
Note musical::NoteService::sharp_to_flat(const Note&note)
{
    if(note.GetPitch()._accid != musical::Accidental::SHARP)
        return note;

    // Trouver l’index de la note dans la liste NAMES
    auto it = NOTE_NAMES_SAXON.begin();
    while (it != NOTE_NAMES_SAXON.end() && *it != note.GetPitch()._name)
        ++it;

    if(it==NOTE_NAMES_SAXON.end())
        throw std::runtime_error("[musical::NoteService::sharp_to_flate] Invalid note name");    

    size_t index = std::distance(NOTE_NAMES_SAXON.begin(), it);        

    // Avancer d’un demi-ton (note suivante)
    size_t new_index = (index + 1) % NOTE_NAMES_SAXON.size(); // boucle cyclique


    char new_name = NOTE_NAMES_SAXON[new_index];        

    return NoteFactory::create(
        new_name,musical::Accidental::FLAT,note.GetPitch()._octave,note.figure());
}
std::string musical::NoteService::from_mei(const std::string&n)
{
    std::map<std::string,std::string> mei_to_saxon
    {
        {"0",  "c"}, 
        {"1s", "g"},
        {"2s", "d"},
        {"3s", "a"},
        {"4s", "e"},
        {"5s", "b"},
        {"6s", "f#"},
        {"7s", "c#"},

        {"1f", "f"},
        {"2f", "bb"},
        {"3f", "eb"},
        {"4f", "ab"},
        {"5f", "db"},
        {"6f", "gb"},
        {"7f", "cb"}
    };

    auto it = mei_to_saxon.find(n);
    if (it != mei_to_saxon.end())
        return it->second;


    std::cerr << "[musical::NoteService::" << __func__ << "]" 
        << "string " << n << "not found in std::map" 
        << std::endl;

    throw std::invalid_argument("mei_to_saxon not found ");


    // if(n=="0")
    //     return Note::all_with_sharp()[0];

    // if (n.ends_with('s')) {
    //     std::string s = n.substr(0, n.size() - 1); // enlever le 's'
    //     int idx = std::stoi(s);
    //     return Note::all_with_sharp()[idx];
    // }

    // if (n.ends_with('f')) {
    //     std::string f = n.substr(0, n.size() - 1); // enlever le 'f'
    //     int idx = std::stoi(f) + 1 + 7;
    //     return Note::all_with_sharp()[idx];
    // }

    // throw std::runtime_error("[Note::from_mei(..)]: format de note MEI inconnu : " + n);
}

