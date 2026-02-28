#pragma once

#include <ostream>
#include <musical/io/chord/input/lexemes.h>

namespace musical::core::chord
{
    class Chord;

    std::ostream& operator<<(std::ostream&, const Chord&);
}

namespace musical::io::chord
{
    std::ostream& operator<<(std::ostream& os, lexeme_t::Category cat);
}
