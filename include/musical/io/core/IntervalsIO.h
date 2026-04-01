#pragma once

#include <cstdint>
#include <ostream>

#include <musical/core/Intervals.h>

namespace musical::core 
{

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

