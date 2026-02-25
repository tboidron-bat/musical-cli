#pragma once

#include <musical/Core/Figure.h>
#include <musical/Core/pitch_t.h>
#include <musical/Core/note/Note.h>

namespace musical::core::note
{

using musical::core::Note;
using musical::core::Figure;
using musical::core::NoteName;
using musical::core::Accidental;
using musical::core::pitch_t;

class Factory
{
public:

    // ------------------------------------------------------------
    // Create from explicit components
    // ------------------------------------------------------------
    static Note create(
        NoteName name,
        Accidental accid,
        int8_t octave,
        Figure figure
    );

    // ------------------------------------------------------------
    // Alteration preference for chromatic creation
    // ------------------------------------------------------------
    enum class AlterationPreference
    {
        SHARP,
        FLAT
    };

    /**
     * @brief Creates a note from a chromatic index.
     *
     * Does NOT handle double-sharps or double-flats.
     *
     * @param chromatic_value Chromatic index in Z.
     *        The value is normalized to the range [0, 11].
     */
    static Note create(
        int chromatic_value,
        int8_t octave = 4,
        Figure figure = Figure(Figure::Type::QUARTER),
        AlterationPreference alterpref = AlterationPreference::SHARP
    );

    // ------------------------------------------------------------
    // Create from char name
    // ------------------------------------------------------------
    static Note create(
        char name,
        Accidental accid,
        int8_t octave,
        Figure figure
    );

    // ------------------------------------------------------------
    // Optional (très propre maintenant)
    // Create directly from pitch_t
    // ------------------------------------------------------------
    static Note create(
        const pitch_t& pitch,
        Figure figure
    );
};

} // namespace musical::core::note