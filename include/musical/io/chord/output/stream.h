#pragma once

#include <ostream>

namespace musical::core::chord
{
    class Chord;

    std::ostream& operator<<(std::ostream&, const Chord&);
}
