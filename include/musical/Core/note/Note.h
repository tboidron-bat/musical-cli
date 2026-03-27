#pragma once

#include <cstdint>
#include <ostream>

#include <musical/Core/Tone.h>
#include <musical/Core/Figure.h>

namespace musical::core::note {
    class Factory;
}

namespace musical::core {

enum class Accidental
{
    NONE,
    SHARP,
    FLAT,
    DOUBLE_SHARP,
    DOUBLE_FLAT
};

class Pitch;

class Note
{
    friend class note::Factory;    
    friend std::ostream& operator<<(std::ostream&, const Note&);    

private:
    enum class Name : uint8_t
    {
        C, D, E, F, G, A, B
    };
private:
    Name  _name;
    Accidental _accidental;
    int8_t     _octave;
    Figure     _figure;

    Note(Name name,
         Accidental accidental,
         int8_t octave,
         Figure figure)
        : _name(name)
        , _accidental(accidental)
        , _octave(octave)
        , _figure(figure)
    {}

public:
    // -------------------------
    // Accesseurs
    // -------------------------
    Tone tone() const noexcept;
    Accidental accidental() const noexcept { return _accidental; }
    int8_t octave() const noexcept { return _octave; }

    const Figure& figure() const { return _figure; }

    // -------------------------
    Pitch to_pitch() const;
    bool operator==(const Note& other) const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Note& note);

}