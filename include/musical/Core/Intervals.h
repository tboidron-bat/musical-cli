#pragma once

#include <cstdint>
#include <ostream>

namespace musical::core {

    enum class Interval : uint8_t {

        ROOT               =  0,  // 
        MINOR_SECOND       =  1,  // b2
        MAJOR_SECOND       =  2,  // 2
        MINOR_THIRD        =  3,  // b3
        MAJOR_THIRD        =  4,  // 3
        PERFECT_FOURTH     =  5,  // 4
        TRITONE            =  6,  // #4 / b5
        PERFECT_FIFTH      =  7,  // 5
        MINOR_SIXTH        =  8,  // b6
        MAJOR_SIXTH        =  9,  // 6
        MINOR_SEVENTH      =  10,  // b7
        MAJOR_SEVENTH      =  11, // 7
        OCTAVE             =  12, // 8

        //Intervalles à l'octave
        MINOR_NINTH        =  13, // b9
        MAJOR_NINTH        =  14, // 9
        MINOR_TENTH        =  15, // b10
        MAJOR_TENTH        =  16, // 10
        PERFECT_ELEVENTH   =  17, // 11
        AUGMENTED_ELEVENTH =  18, // #11
        PERFECT_TWELFTH    =  19, // 12
        MINOR_THIRTEENTH   =  20, // b13
        MAJOR_THIRTEENTH   =  21, // 13
        MINOR_FOURTEENTH   =  22, // b14
        MAJOR_FOURTEENTH   =  23, // 14
        FIFTEENTH          =  24, // 15 (double octave)
    };


inline std::ostream& operator<<(std::ostream& os, Interval type)
{
    switch (type)
    {
        case Interval::ROOT:                 os << "root"; break;

        case Interval::MINOR_SECOND:         os << "minor second"; break;
        case Interval::MAJOR_SECOND:         os << "major second"; break;

        case Interval::MINOR_THIRD:          os << "minor third"; break;
        case Interval::MAJOR_THIRD:          os << "major third"; break;

        case Interval::PERFECT_FOURTH:       os << "perfect fourth"; break;
        case Interval::TRITONE:              os << "tritone"; break;

        case Interval::PERFECT_FIFTH:        os << "perfect fifth"; break;

        case Interval::MINOR_SIXTH:          os << "minor sixth"; break;
        case Interval::MAJOR_SIXTH:          os << "major sixth"; break;

        case Interval::MINOR_SEVENTH:        os << "minor seventh"; break;
        case Interval::MAJOR_SEVENTH:        os << "major seventh"; break;

        case Interval::OCTAVE:               os << "octave"; break;

        case Interval::MINOR_NINTH:          os << "minor ninth"; break;
        case Interval::MAJOR_NINTH:          os << "major ninth"; break;

        case Interval::MINOR_TENTH:          os << "minor tenth"; break;
        case Interval::MAJOR_TENTH:          os << "major tenth"; break;

        case Interval::PERFECT_ELEVENTH:     os << "perfect eleventh"; break;
        case Interval::AUGMENTED_ELEVENTH:   os << "augmented eleventh"; break;

        case Interval::PERFECT_TWELFTH:      os << "perfect twelfth"; break;

        case Interval::MINOR_THIRTEENTH:     os << "minor thirteenth"; break;
        case Interval::MAJOR_THIRTEENTH:     os << "major thirteenth"; break;

        case Interval::MINOR_FOURTEENTH:     os << "minor fourteenth"; break;
        case Interval::MAJOR_FOURTEENTH:     os << "major fourteenth"; break;

        case Interval::FIFTEENTH:            os << "fifteenth"; break;

        default:                            os << "unknown"; break;
    }

    return os;
}
inline const char* to_symbol(Interval it)
{
    using I = Interval;

    switch (it)
    {
        case I::ROOT:                return "1";

        case I::MINOR_SECOND:        return "b2";
        case I::MAJOR_SECOND:        return "2";

        case I::MINOR_THIRD:         return "b3";
        case I::MAJOR_THIRD:         return "3M";

        case I::PERFECT_FOURTH:      return "4";
        case I::TRITONE:             return "b5";   // ou "#4"

        case I::PERFECT_FIFTH:       return "5";

        case I::MINOR_SIXTH:         return "b6";
        case I::MAJOR_SIXTH:         return "6";

        case I::MINOR_SEVENTH:       return "b7";
        case I::MAJOR_SEVENTH:       return "7M";

        case I::OCTAVE:              return "8";

        case I::MINOR_NINTH:         return "b9";
        case I::MAJOR_NINTH:         return "9";

        case I::MINOR_TENTH:         return "b10";
        case I::MAJOR_TENTH:         return "10";

        case I::PERFECT_ELEVENTH:    return "11";
        case I::AUGMENTED_ELEVENTH:  return "#11";

        case I::PERFECT_TWELFTH:     return "12";

        case I::MINOR_THIRTEENTH:    return "b13";
        case I::MAJOR_THIRTEENTH:    return "13";

        case I::MINOR_FOURTEENTH:    return "b14";
        case I::MAJOR_FOURTEENTH:    return "14";

        case I::FIFTEENTH:           return "15";
    }

    return "?";
}
}

