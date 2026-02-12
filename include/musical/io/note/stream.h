#pragma once

#include <ostream>

namespace musical::core
{
    class Note;

    std::ostream& operator<<(std::ostream&, const Note&);
}
