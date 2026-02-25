#include <musical/Core/note/Note.h>
 #include <array>


namespace musical::core {

bool Note::operator==(const Note& other) const noexcept {
    return this->_pitch._name     == other._pitch._name &&
           this->_pitch._octave   == other._pitch._octave &&
           this->_pitch._accidental    == other._pitch._accidental &&
           this->_figure == other._figure;
}
}


