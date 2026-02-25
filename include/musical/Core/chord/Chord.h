#pragma once

#include <vector>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/ChordType.h>

namespace musical::core::chord {

class Chord
{
private:
    pitch_t _tonic;
    ChordType _type;

public:

    Chord(pitch_t tonic, ChordType type)
        : _tonic(std::move(tonic))
        , _type(std::move(type))
    {}

    // ------------------------------------------------------------
    // Accesseurs
    // ------------------------------------------------------------
    const pitch_t& root() const noexcept { return _tonic; }

    const ChordType& type() const noexcept { return _type; }

    std::size_t size() const;

    std::vector<pitch_t> notes(bool with_sharp = true) const;
};

} // namespace musical::core::chord