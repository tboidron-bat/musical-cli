#pragma once

#include <string>
#include <ostream>

#include <musical/core/Pitch.h>

#include <musical/io/core/ToneIO.h>

namespace musical::core
{
inline std::ostream& operator<<(std::ostream&os,const Pitch&pitch)
{
     return os << pitch.tone()  << static_cast<int>(pitch.octave());
}
}
