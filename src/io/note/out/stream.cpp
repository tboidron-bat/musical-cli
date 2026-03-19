#include <musical/io/note/out/stream.h>
#include <musical/io/note/out/note_formatter.h>

#include <musical/Core/pitch_t.h>
#include <musical/Core/note/Note.h>

namespace musical::core
{

std::ostream& operator<<(std::ostream& os, const pitch_t& pitch)
{
    os << musical::io::note::formatter::to_string(pitch);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Note& note)
{
    // on reconstruit un pitch_t depuis Note
    pitch_t p;
    p._name       = note.name();
    p._accidental = note.accidental();
    p._octave     = note.octave();

    os << p;
    return os;
}

}