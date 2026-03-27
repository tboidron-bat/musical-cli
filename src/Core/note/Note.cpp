#include <musical/Core/note/Note.h>
#include <musical/Core/Pitch.h>
 #include <array>


namespace musical::core {

Pitch Note::to_pitch() const
{
    return Pitch(tone(), _octave);
}
Tone Note::tone() const noexcept
{
    int base = 0;

    switch(_name)
    {
        case Name::C: base = 0; break;
        case Name::D: base = 2; break;
        case Name::E: base = 4; break;
        case Name::F: base = 5; break;
        case Name::G: base = 7; break;
        case Name::A: base = 9; break;
        case Name::B: base = 11; break;
    }

    int offset = 0;
    switch(_accidental)
    {
        case Accidental::SHARP: offset = 1; break;
        case Accidental::FLAT: offset = -1; break;
        case Accidental::DOUBLE_SHARP: offset = 2; break;
        case Accidental::DOUBLE_FLAT: offset = -2; break;
        default: break;
    }

    int semitone = (base + offset + 12) % 12;

    return static_cast<Tone>(semitone);
}

bool Note::operator==(const Note& other) const noexcept {
        return _name == other._name &&
               _accidental == other._accidental &&
               _octave == other._octave;
}

std::ostream& operator<<(std::ostream& os, const Note& note)
{
    // Nom de base (IMPORTANT : utiliser _name, pas tone())
    switch(note._name)
    {
        case Note::Name::C: os << "C"; break;
        case Note::Name::D: os << "D"; break;
        case Note::Name::E: os << "E"; break;
        case Note::Name::F: os << "F"; break;
        case Note::Name::G: os << "G"; break;
        case Note::Name::A: os << "A"; break;
        case Note::Name::B: os << "B"; break;
    }

    // Altération
    switch(note._accidental)
    {
        case Accidental::SHARP:         os << "#"; break;
        case Accidental::FLAT:          os << "b"; break;
        case Accidental::DOUBLE_SHARP:  os << "##"; break;
        case Accidental::DOUBLE_FLAT:   os << "bb"; break;
        case Accidental::NONE:          break;
    }

    // Octave
    os << static_cast<int>(note._octave);

    return os;
}
}


