#pragma once

#include <cstdint>

#include <musical/core/Tone.h>

namespace musical::core
{

class Pitch
{
private:
    uint8_t _value; //MIDI : 0–127

public:
    constexpr Pitch() : _value(0) {}

    constexpr explicit Pitch(uint8_t value)
        : _value(value) {}

    constexpr Pitch(Tone tone, int8_t octave)
        : _value(static_cast<uint8_t>(static_cast<uint8_t>(tone) + (octave+1) * 12)) 
    {}

    // ========================
    // ACCESSEURS
    // ========================
    constexpr uint8_t value() const
    {
        return _value;
    }
    constexpr Tone tone() const
    {
        return static_cast<Tone>(_value % 12);
    }
    constexpr int8_t octave() const
    {
        return static_cast<int8_t>(_value / 12 /* -1 ? */); 
    }
    // ========================
    // OPERATEURS
    // ========================
    constexpr bool operator==(const Pitch& other) const
    {
        return _value == other._value;
    }
    constexpr bool operator!=(const Pitch& other) const
    {
        return !(*this == other);
    }
    constexpr bool operator<(const Pitch& other) const
    {
        return _value < other._value;
    }
};
} // namespace musical::core