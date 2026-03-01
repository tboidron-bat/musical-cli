#pragma once

#include <ostream>
#include <musical/io/chord/input/lexemes.h>
#include <musical/Core/intervals_defs.h>

namespace musical::core::chord
{
    class Chord;

    std::ostream& operator<<(std::ostream&, const Chord&);
}

namespace musical::io::chord
{
    std::ostream& operator<<(std::ostream& os, lexeme_t::Category cat);
}
namespace musical::core
{
    std::ostream& operator<<(std::ostream& os, core::IntervalType);
}

