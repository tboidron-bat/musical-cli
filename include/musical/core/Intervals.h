#pragma once

#include <cstdint>

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
}

