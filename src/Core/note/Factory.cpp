#include <musical/Core/note/Factory.h>
#include <musical/Core/note/Note.h>

#include <stdexcept>
#include <cctype>
#include <array>

namespace musical::core::note
{

// ------------------------------------------------------------
// Create from explicit components
// ------------------------------------------------------------
Note 
Factory::create(
    NoteName name,
    Accidental accid,
    int8_t octave,
    Figure figure)
{
    return Note(name, accid, octave, figure);
}


// ------------------------------------------------------------
// Create from chromatic value
// ------------------------------------------------------------
Note 
Factory::create(
    int chromatic_value, 
    int8_t octave, 
    Figure figure,
    AlterationPreference alterpref)
{
    // Normalisation robuste 0–11 (gère les valeurs négatives)
    chromatic_value = ((chromatic_value % 12) + 12) % 12;

    // Valeurs naturelles (C D E F G A B)
    static constexpr std::array<int, 7> natural_values =
        {0, 2, 4, 5, 7, 9, 11};

    static constexpr std::array<NoteName, 7> natural_names =
        {
            NoteName::C,
            NoteName::D,
            NoteName::E,
            NoteName::F,
            NoteName::G,
            NoteName::A,
            NoteName::B
        };

    // 1️⃣ Cas naturel
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
    // Normalisation en minuscule
    char n = static_cast<char>(
        std::tolower(static_cast<unsigned char>(name))
    );

    NoteName note_name;

    switch (n)
    {
        case 'c': note_name = NoteName::C; break;
        case 'd': note_name = NoteName::D; break;
        case 'e': note_name = NoteName::E; break;
        case 'f': note_name = NoteName::F; break;
        case 'g': note_name = NoteName::G; break;
        case 'a': note_name = NoteName::A; break;
        case 'b': note_name = NoteName::B; break;

        default:
            throw std::invalid_argument(
                "[NoteFactory]::create: invalid note name"
            );
    }

    return Note(note_name, accid, octave, figure);
}


// ------------------------------------------------------------
// Optional: create from pitch_t
// ------------------------------------------------------------
Note
Factory::create(
    const pitch_t& pitch,
    Figure figure)
{
    return Note(pitch._name, pitch._accidental, pitch._octave, figure);
}

} // namespace musical::core::note