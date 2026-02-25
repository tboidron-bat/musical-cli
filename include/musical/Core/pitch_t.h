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

    bool operator==(const pitch_t&) const noexcept = default;
    bool operator!=(const pitch_t&) const noexcept = default;

    // utile pour map / set
    bool operator<(const pitch_t& other) const noexcept;
};

std::size_t chromatic_index(const pitch_t&) noexcept;

pitch_t pitch_from_chromatic(int chromatic_index, bool with_sharp) noexcept;

pitch_t pitch_from_chromatic_index(
    int index,
    bool with_sharp = true
);

} // namespace musical::core