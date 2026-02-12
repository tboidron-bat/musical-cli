#include <musical/io/note/stream.h>

#include <musical/io/note/note_formatter.h>

namespace musical::core
{
    std::ostream& operator<<(std::ostream& os, const Note& note)
    {
        os << musical::io::note::formatter::to_string(note);
        return os;
    }
}
