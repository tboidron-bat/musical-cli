#include <musical/io/note/note_parser.h>
#include <musical/io/common/const_notations.h>
#include <musical/Core/note/Factory.h>

#include <algorithm>
#include <stdexcept>
#include <cctype>

namespace musical::io::note {

core::Note parse_from_saxon(
    const std::string& name,
    uint8_t default_octave,
    Figure default_figure)
{
    if (name.empty())
        throw std::invalid_argument("[parse_from_saxon] Empty note string");

    // Normalisation en minuscules
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    char letter = name[0];

    // --- Conversion char -> enum Name ---
    using Name = core::Note::Name;
    using Acc  = core::Note::Accidental;

    Name note_name;

    switch(letter)
    {
        case 'c': note_name = Name::C; break;
        case 'd': note_name = Name::D; break;
        case 'e': note_name = Name::E; break;
        case 'f': note_name = Name::F; break;
        case 'g': note_name = Name::G; break;
        case 'a': note_name = Name::A; break;
        case 'b': note_name = Name::B; break;
        default:
            throw std::invalid_argument("[parse_from_saxon] Invalid note letter: " + name);
    }

    // --- Détection altération ---
    Acc accid = Acc::NONE;

    if (name.size() == 2)
    {
        if (name[1] == musical::notation::SHARP_ASCII)
            accid = Acc::SHARP;
        else if (name[1] == musical::notation::FLAT_ASCII)
            accid = Acc::FLAT;
        else
            throw std::invalid_argument("[parse_from_saxon] Invalid accidental: " + name);
    }
    else if (name.size() == 3)
    {
        if (name[1] == musical::notation::FLAT_ASCII &&
            name[2] == musical::notation::FLAT_ASCII)
            accid = Acc::DOUBLE_FLAT;
        else if (name[1] == musical::notation::SHARP_ASCII &&
                 name[2] == musical::notation::SHARP_ASCII)
            accid = Acc::DOUBLE_SHARP;
        else
            throw std::invalid_argument("[parse_from_saxon] Invalid double accidental: " + name);
    }
    else if (name.size() > 3)
    {
        throw std::invalid_argument("[parse_from_saxon] Note string too long: " + name);
    }

    // --- Création via la factory Core ---
    return musical::core::note::Factory::create(
        note_name,
        accid,
        default_octave,
        default_figure
    );
}

} // namespace musical::io::note



// #include <musical/io/note/note_parser.h>
// #include <musical/io/common/const_notations.h>
// #include <musical/Core/note/Factory.h>

// #include <algorithm>
// #include <stdexcept>
// #include <cctype>

// namespace musical::io::note {

// core::Note parse_from_saxon(
//     std::string name,
//     uint8_t default_octave,
//     Figure default_figure)
// {
//     if (name.empty())
//         throw std::invalid_argument("[parse_from_saxon] Empty note string");

//     // Normalisation en minuscules
//     std::transform(name.begin(), name.end(), name.begin(),
//                    [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

//     char letter = name[0];

//     // --- Conversion char -> enum Name ---
//     using Name = core::Note::Name;
//     using Acc  = core::Note::Accidental;

//     Name note_name;

//     switch(letter)
//     {
//         case 'c': note_name = Name::C; break;
//         case 'd': note_name = Name::D; break;
//         case 'e': note_name = Name::E; break;
//         case 'f': note_name = Name::F; break;
//         case 'g': note_name = Name::G; break;
//         case 'a': note_name = Name::A; break;
//         case 'b': note_name = Name::B; break;
//         default:
//             throw std::invalid_argument("[parse_from_saxon] Invalid note letter: " + name);
//     }

//     // --- Détection altération ---
//     Acc accid = Acc::NONE;

//     if (name.size() == 2)
//     {
//         if (name[1] == musical::notation::SHARP_ASCII)
//             accid = Acc::SHARP;
//         else if (name[1] == musical::notation::FLAT_ASCII)
//             accid = Acc::FLAT;
//         else
//             throw std::invalid_argument("[parse_from_saxon] Invalid accidental: " + name);
//     }
//     else if (name.size() == 3)
//     {
//         if (name[1] == musical::notation::FLAT_ASCII &&
//             name[2] == musical::notation::FLAT_ASCII)
//             accid = Acc::DOUBLE_FLAT;
//         else if (name[1] == musical::notation::SHARP_ASCII &&
//                  name[2] == musical::notation::SHARP_ASCII)
//             accid = Acc::DOUBLE_SHARP;
//         else
//             throw std::invalid_argument("[parse_from_saxon] Invalid double accidental: " + name);
//     }
//     else if (name.size() > 3)
//     {
//         throw std::invalid_argument("[parse_from_saxon] Note string too long: " + name);
//     }

//     // --- Création via la factory Core ---
//     return musical::core::NoteFactory::create(
//         note_name,
//         accid,
//         default_octave,
//         default_figure
//     );
// }

// } // namespace musical::io::note
