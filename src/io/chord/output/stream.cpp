#include <musical/io/chord/output/stream.h>

#include <musical/io/chord/formatter.h>


namespace musical::core::chord
{
    std::ostream& operator<<(std::ostream& os, const Chord& chord)
    {
        os << musical::io::chord::formatter::to_string(chord);
        return os;
    }
}
