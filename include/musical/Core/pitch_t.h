#pragma once

#include <cstdint>

namespace musical::core
{

enum class NoteName : uint8_t
{
    C, D, E, F, G, A, B
};

enum class Accidental
{
    NONE,
    SHARP,
    FLAT,
    DOUBLE_SHARP,
    DOUBLE_FLAT
};

struct pitch_t
{
    NoteName  _name;
    Accidental _accidental;
    uint8_t    _octave;   

    NoteName name() const noexcept { return _name; }
    Accidental accidental() const noexcept { return _accidental; }
    uint8_t octave() const noexcept { return _octave; }

    bool operator==(const pitch_t& other) const noexcept;

    bool operator!=(const pitch_t& other) const noexcept
    {
        return !(*this == other);
    }

    // utile pour map / set
    bool operator<(const pitch_t& other) const noexcept;
    pitch_t& operator+=( uint8_t semitones);
};

std::size_t chromatic_index(const pitch_t&) noexcept;

pitch_t pitch_from_chromatic_index(
    int index,
    bool with_sharp = true
);

} // namespace musical::core