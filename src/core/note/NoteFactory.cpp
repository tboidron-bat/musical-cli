#include <musical/core/note/NoteFactory.h>
#include <musical/core/note/Note.h>

#include <stdexcept>


namespace musical::core::note
{

// ------------------------------------------------------------
// Create from Tone
// ------------------------------------------------------------
Note 
Factory::create(
    Tone tone,
    uint8_t octave,
    Figure figure,
    AlterationPreference pref)
{
    using N = Note::Name;

    switch(tone)
    {
        case Tone::C:  return Note(N::C, Accidental::NONE, octave, figure);

        case Tone::Cs:
            return (pref == AlterationPreference::SHARP)
                ? Note(N::C, Accidental::SHARP, octave, figure)
                : Note(N::D, Accidental::FLAT,  octave, figure);

        case Tone::D:  return Note(N::D, Accidental::NONE, octave, figure);

        case Tone::Ds:
            return (pref == AlterationPreference::SHARP)
                ? Note(N::D, Accidental::SHARP, octave, figure)
                : Note(N::E, Accidental::FLAT,  octave, figure);

        case Tone::E:  return Note(N::E, Accidental::NONE, octave, figure);

        case Tone::F:  return Note(N::F, Accidental::NONE, octave, figure);

        case Tone::Fs:
            return (pref == AlterationPreference::SHARP)
                ? Note(N::F, Accidental::SHARP, octave, figure)
                : Note(N::G, Accidental::FLAT,  octave, figure);

        case Tone::G:  return Note(N::G, Accidental::NONE, octave, figure);

        case Tone::Gs:
            return (pref == AlterationPreference::SHARP)
                ? Note(N::G, Accidental::SHARP, octave, figure)
                : Note(N::A, Accidental::FLAT,  octave, figure);

        case Tone::A:  return Note(N::A, Accidental::NONE, octave, figure);

        case Tone::As:
            return (pref == AlterationPreference::SHARP)
                ? Note(N::A, Accidental::SHARP, octave, figure)
                : Note(N::B, Accidental::FLAT,  octave, figure);

        case Tone::B:  return Note(N::B, Accidental::NONE, octave, figure);
    }

    throw std::logic_error("NoteFactory: invalid Tone");
}


// ------------------------------------------------------------
// Create from char
// ------------------------------------------------------------
Note 
Factory::create(
    char name,
    Accidental accid,
    int8_t octave,
    Figure figure)
{
    using N = Note::Name;

    char n = static_cast<char>(
        std::tolower(static_cast<unsigned char>(name))
    );

    switch (n)
    {
        case 'c': return Note(N::C, accid, octave, figure);
        case 'd': return Note(N::D, accid, octave, figure);
        case 'e': return Note(N::E, accid, octave, figure);
        case 'f': return Note(N::F, accid, octave, figure);
        case 'g': return Note(N::G, accid, octave, figure);
        case 'a': return Note(N::A, accid, octave, figure);
        case 'b': return Note(N::B, accid, octave, figure);

        default:
            throw std::invalid_argument(
                "[NoteFactory]::create: invalid note name"
            );
    }
}


// ------------------------------------------------------------
// Create from Pitch
// ------------------------------------------------------------
Note
Factory::create(
    const Pitch& pitch,
    Figure figure,
    AlterationPreference pref)
{
    return create(pitch.tone(), pitch.octave(), figure, pref);
}

} // namespace musical::core::note