#pragma once

#include <ostream>

#include <musical/chord_db/Diagram.h>

namespace chord::db 
{
    std::ostream& operator <<(std::ostream& os, Diagram::CAGED shape)
    {
        switch (shape)
        {
            case Diagram::CAGED::C: return os << "[C]aged";
            case Diagram::CAGED::A: return os << "c[A]ged";
            case Diagram::CAGED::G: return os << "ca[G]ed";
            case Diagram::CAGED::E: return os << "cag[E]d";
            case Diagram::CAGED::D: return os << "cage[D]";
        }
        return os;
    }

    std::string to_string(Diagram::CAGED shape)
    {
        switch (shape)
        {
            case Diagram::CAGED::C: return "[C]aged";
            case Diagram::CAGED::A: return "c[A]ged";
            case Diagram::CAGED::G: return "ca[G]ed";
            case Diagram::CAGED::E: return "cag[E]d";
            case Diagram::CAGED::D: return "cage[D]";
        }
        return "unknown";
    }
}

// inline std::ostream& operator<<(std::ostream& os,
//                                 Diagram::CAGED shape)
// {
//     switch (shape)
//     {
//         case Diagram::CAGED::C: return os << "C";
//         case Diagram::CAGED::A: return os << "A";
//         case Diagram::CAGED::G: return os << "G";
//         case Diagram::CAGED::E: return os << "E";
//         case Diagram::CAGED::D: return os << "D";
//     }
//     return os;
// }


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

// enum class GuitarChordStyle : uint16_t
// {
//     NONE         = 0,
//     CLASSICAL    = 1 << 0,
//     FLAMENCO     = 1 << 1,
//     ROCK         = 1 << 2,
//     JAZZ         = 1 << 3,
//     BLUES        = 1 << 4,
//     FUNK         = 1 << 5,
//     AMBIENT      = 1 << 6,
//     PINKFLOYDIAN = 1 << 7,
//     BRANDXIAN    = 1 << 8,
// };    

