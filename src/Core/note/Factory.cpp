#include <musical/Core/note/Factory.h>
#include <musical/Core/note/Note.h>

#include <stdexcept>
#include <cctype>
#include <array>

namespace musical::core::note
{

Note 
Factory::create(
    int chromatic_value, 
    uint8_t octave, 
    Figure figure,
    AlterationPreference alterpref)
{
    using Name       = Note::Name;
    using Accidental = Note::Accidental;

    // Normalisation robuste 0–11 (gère les valeurs négatives)
    chromatic_value = ((chromatic_value % 12) + 12) % 12;

    // Valeurs naturelles (C D E F G A B)
    static constexpr std::array<int, 7> natural_values =
        {0, 2, 4, 5, 7, 9, 11};

    static constexpr std::array<Name, 7> natural_names =
        {Name::C, Name::D, Name::E, Name::F, Name::G, Name::A, Name::B};

    // 1️⃣ Cas naturel (sans altération)
    for (size_t i = 0; i < natural_values.size(); ++i)
    {
        if (natural_values[i] == chromatic_value)
        {
            return Note(natural_names[i], Accidental::NONE, octave, figure);
        }
    }

    // 2️⃣ Cas altéré
    int base_val;
    Accidental accid;

    if (alterpref == AlterationPreference::SHARP)
    {
        base_val = (chromatic_value + 11) % 12; // -1 modulo 12
        accid = Accidental::SHARP;
    }
    else
    {
        base_val = (chromatic_value + 1) % 12; // +1 modulo 12
        accid = Accidental::FLAT;
    }

    for (size_t i = 0; i < natural_values.size(); ++i)
    {
        if (natural_values[i] == base_val)
        {
            return Note(natural_names[i], accid, octave, figure);
        }
    }

    throw std::logic_error("NoteFactory: unable to resolve chromatic value");
}

Note 
Factory::create(
    char name,
    Note::Accidental accid,
    uint8_t octave,
    Figure figure)
{
    using Name = Note::Name;

    // Normalisation en minuscule
    char n = static_cast<char>(
        std::tolower(static_cast<unsigned char>(name))
    );

    Name note_name;

    switch (n)
    {
        case 'c': note_name = Name::C; break;
        case 'd': note_name = Name::D; break;
        case 'e': note_name = Name::E; break;
        case 'f': note_name = Name::F; break;
        case 'g': note_name = Name::G; break;
        case 'a': note_name = Name::A; break;
        case 'b': note_name = Name::B; break;
        default:
            throw std::invalid_argument(
                "[NoteFactory]::create: invalid note name"
            );
    }

    return Note(note_name, accid, octave, figure);
}
}