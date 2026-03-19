#pragma once

#include <musical/guitar_chord_database/Diagram.h>
#include <ostream>
#include <sstream>
#include <string>

namespace chord::database {

inline std::ostream& operator<<(std::ostream& os,
                                Diagram::CAGED shape)
{
    switch (shape)
    {
        case Diagram::CAGED::C: return os << "C";
        case Diagram::CAGED::A: return os << "A";
        case Diagram::CAGED::G: return os << "G";
        case Diagram::CAGED::E: return os << "E";
        case Diagram::CAGED::D: return os << "D";
    }
    return os;
}

// inline std::ostream& operator<<(std::ostream& os,
//                                 Diagram::Style s)
// {
//     using Style = Diagram::Style;

//     switch (s)
//     {
//         case Style::CLASSICAL: return os << "classical";
//         case Style::FLAMENCO:  return os << "flamenco";
//         case Style::ROCK:      return os << "rock";
//         case Style::JAZZ:      return os << "jazz";
//         case Style::BLUES:     return os << "blues";
//         case Style::FUNK:      return os << "funk";
//         default:               return os << "none";
//     }
// }

// inline std::string style_mask_to_string(uint16_t mask)
// {
//     using Style = Diagram::Style;

//     std::ostringstream oss;
//     bool first = true;

//     auto print_if = [&](Style s)
//     {
//         if (mask & static_cast<uint16_t>(s))
//         {
//             if (!first) oss << ",";
//             oss << s;
//             first = false;
//         }
//     };

//     print_if(Style::CLASSICAL);
//     print_if(Style::FLAMENCO);
//     print_if(Style::ROCK);
//     print_if(Style::JAZZ);
//     print_if(Style::BLUES);
//     print_if(Style::FUNK);

//     if (first)
//         oss << "none";

//     return oss.str();
// }


// inline std::istream& operator>>(std::istream& is, StyleMask& sm)
// {
//     using Style = Diagram::Style;

//     std::string input;
//     is >> input;

//     std::stringstream ss(input);
//     std::string token;

//     sm.value = 0;

//     while (std::getline(ss, token, ','))
//     {
//         auto opt = style_from_string(token);
//         if (!opt)
//         {
//             is.setstate(std::ios::failbit);
//             return is;
//         }

//         sm.value |= static_cast<uint16_t>(*opt);
//     }

//     return is;
// }

}