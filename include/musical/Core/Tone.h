#pragma once

#include <cstdint>
#include <ostream>

namespace musical::core
{
    enum class Tone : uint8_t
    {
        C  = 0,
        Cs = 1, Df = 1,
        D  = 2,
        Ds = 3, Ef = 3,
        E  = 4,
        F  = 5,
        Fs = 6, Gf = 6,
        G  = 7,
        Gs = 8, Af = 8,
        A  = 9,
        As = 10, Bf = 10,
        B  = 11
    };

inline std::ostream& operator<<(std::ostream& os, Tone tone)
{
    // ⚠️ IMPORTANT :
    // Tone contient des alias (Cs == Df, Ds == Ef, etc.)
    // On ne peut PAS différencier # et b ici.
    // On choisit donc une représentation canonique (ici : dièses).
    //
    // 👉 Alternative possible :
    // utiliser les bémols à la place :
    // C, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B

    switch(tone)
    {
        case Tone::C:  return os << "C";
        case Tone::Cs: return os << "C#"; // ou "Db"
        case Tone::D:  return os << "D";
        case Tone::Ds: return os << "D#"; // ou "Eb"
        case Tone::E:  return os << "E";
        case Tone::F:  return os << "F";
        case Tone::Fs: return os << "F#"; // ou "Gb"
        case Tone::G:  return os << "G";
        case Tone::Gs: return os << "G#"; // ou "Ab"
        case Tone::A:  return os << "A";
        case Tone::As: return os << "A#"; // ou "Bb"
        case Tone::B:  return os << "B";
    }

    return os;
}
}
