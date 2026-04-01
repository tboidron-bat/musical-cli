#pragma once

#include <ostream>

#include <musical/core/chord/Chord.h>

#include <musical/io/core/PitchIO.h>
#include <musical/io/core/chord/ChordTypeIO.h>

namespace musical::core::chord {

inline std::ostream& operator<<(std::ostream& os, const Chord& chord)
{
    os << chord.root()
       << " "
       << chord.type();

    return os;
}


}