#pragma once

#include <ostream>
#include <musical/Core/pitch_t.h>
#include <musical/Core/note/Note.h>

namespace musical::core
{
    std::ostream& operator<<(std::ostream& os, const pitch_t& pitch);
    std::ostream& operator<<(std::ostream& os, const Note& note);
}