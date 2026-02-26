#include <musical/io/chord/output/stream.h>

#include <musical/io/chord/output/formatter.h>


namespace musical::core::chord
{
    std::ostream& operator<<(std::ostream& os, const Chord& chord)
    {
        os << musical::io::chord::formatter::to_string(chord);
        return os;
    }
}

namespace musical::io::chord
{
    std::ostream& operator<<(std::ostream& os, LexemeCategory cat)
    {
        using C = LexemeCategory;

        switch (cat)
        {
            case C::TRIAD:       os << "TRIAD"; break;
            case C::SEVENTH:     os << "SEVENTH"; break;
            case C::EXTENSION:   os << "EXTENSION"; break;
            case C::ALTERATION:  os << "ALTERATION"; break;
            case C::SUSPENSION:  os << "SUSPENSION"; break;
            case C::ADDITION:    os << "ADDITION"; break;
            case C::SPECIAL:     os << "SPECIAL"; break;
            default:             os << "UNKNOWN"; break;
        }

        return os;
    }
}
