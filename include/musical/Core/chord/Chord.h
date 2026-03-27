#pragma once

#include <vector>

#include <musical/Core/Pitch.h>
#include <musical/Core/chord/ChordType.h>

namespace musical::core::chord {

class Chord
{
private:
    Pitch _root;
    ChordType _type;

public:

    Chord(Pitch root, ChordType type)
        : _root(root)
        , _type(std::move(type))
    {}

    // ------------------------------------------------------------
    // Accesseurs
    // ------------------------------------------------------------
    Tone tone() const noexcept { return _root.tone(); }

    const Pitch& root() const noexcept { return _root; }    
    const ChordType& type() const noexcept { return _type; }

    std::size_t size() const;

    std::vector<Pitch> notes() const;
};

std::ostream& operator<<(std::ostream&, const Chord&);

} // namespace musical::core::chord