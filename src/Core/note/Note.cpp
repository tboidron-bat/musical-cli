#include <musical/Core/note/Note.h>
#include <musical/Core/note/NoteService.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <cctype>

namespace musical {

Note::Note(char name,Accidental accid,uint8_t octave,Figure f)
:
_pitch{name, accid, octave}, _figure(f)
{}


bool Note::operator==(const Note& other) const {
    return this->_pitch._name     == other._pitch._name &&
           this->_pitch._octave   == other._pitch._octave &&
           this->_pitch._accid    == other._pitch._accid &&
           this->_figure == other._figure;
}
 std::ostream& operator<<(std::ostream& os, const Note& note)
{
    os << musical::NoteService::to_string(note);
    //os << "[" << note.figure().to_string() << "]";
    return os;
}
}


