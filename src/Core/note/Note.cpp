#include <musical/Core/note/Note.h>
 #include <array>


namespace musical::core {

bool Note::operator==(const Note& other) const noexcept {
    return this->_pitch._name     == other._pitch._name &&
           this->_pitch._octave   == other._pitch._octave &&
           this->_pitch._accid    == other._pitch._accid &&
           this->_figure == other._figure;
}
std::size_t Note::chromatic_index() const noexcept
{
    // Table de correspondance des noms de base

    static constexpr std::array<int, 7> base_values = {
        0,  // C
        2,  // D
        4,  // E
        5,  // F
        7,  // G
        9,  // A
        11  // B
    };

    int base = base_values[static_cast<std::size_t>(_pitch._name)];

    int offset = 0;

    switch (_pitch._accid) {
        case Note::Accidental::SHARP:        
            offset = 1; break;
        case Note::Accidental::FLAT:         
            offset = -1; break;
        case Note::Accidental::DOUBLE_SHARP: 
            offset = 2; break;
        case Note::Accidental::DOUBLE_FLAT:  
            offset = -2; break;
        default: break;
    }

    return (base + offset + 12) % 12;
}

//  std::ostream& operator<<(std::ostream& os, const Note& note)
// {
//     os << musical::io::note::to_string(note);
//     //os << "[" << note.figure().to_string() << "]";
//     return os;
// }
}


