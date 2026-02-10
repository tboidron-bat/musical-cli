#ifndef MUSICAL_CORE_CONSTANTS_H
#define MUSICAL_CORE_CONSTANTS_H

#include <array>

namespace musical {

    constexpr unsigned int CHROMATIC_NOTE_COUNT = 12;
    constexpr unsigned int NOTE_COUNT = 7;
    constexpr char SHARP_CHAR = '#';
    constexpr char FLAT_CHAR = 'b';

    inline constexpr std::array<char, NOTE_COUNT> NOTE_NAMES_SAXON =  { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };

}

#endif