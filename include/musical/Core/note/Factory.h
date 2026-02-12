    #pragma once

#include <musical/Core/Figure.h>
#include <musical/Core/note/Note.h>

namespace musical::core::note
{

using musical::core::Note;
using musical::core::Figure;

class Factory
{
public:

    static Note create(
        Note::Name name,
        Note::Accidental accid,
        uint8_t octave,
        Figure figure
    );


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
        uint8_t octave = 4,
        Figure figure = Figure(Figure::Type::QUARTER),
        AlterationPreference alterpref = AlterationPreference::SHARP
    );

    static Note create(
        char name,
        Note::Accidental accid,
        uint8_t octave,
        Figure figure
    );
};

}
