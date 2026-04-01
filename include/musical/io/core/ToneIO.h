#pragma once

#include <musical/core/Tone.h>

#include <array>
#include <ostream>

namespace musical::io::core
{

enum class Accidental
{
    Sharp,
    Flat
};

inline std::string to_string(musical::core::Tone tone, Accidental pref)
{
    static const std::array<std::string, 12> sharp_names =
    {
        "C","C#","D","D#","E","F","F#","G","G#","A","A#","B"
    };

    static const std::array<std::string, 12> flat_names =
    {
        "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"
    };

    uint8_t index = static_cast<uint8_t>(tone);

    return (pref == Accidental::Sharp)
        ? sharp_names[index]
        : flat_names[index];
}
}

namespace musical::core
{
inline std::ostream& operator<<(std::ostream& os, Tone tone)
{
    // ⚠️ IMPORTANT :
    // Tone contient des alias (Cs == Df, Ds == Ef, etc.)
    // On ne peut PAS différencier # et b ici.
    // On choisit donc une représentation canonique (ici : dièses).

    os << musical::io::core::to_string(
        tone,
        musical::io::core::Accidental::Sharp);

    return os;
}
}
