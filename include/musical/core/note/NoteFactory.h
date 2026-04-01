#pragma once

#include <cstdint>

#include <musical/core/Figure.h>
#include <musical/core/Pitch.h>
#include <musical/core/note/Note.h>

namespace musical::core::note
{

class Factory
{
public:

    // ------------------------------------------------------------
    // Alteration preference 
    // ------------------------------------------------------------
    enum class AlterationPreference
    {
        SHARP,
        FLAT
    };

    // ------------------------------------------------------------
    // Create from Tone (safe version)
    // ------------------------------------------------------------
    static Note create(
        Tone tone,
        uint8_t octave = 4,
        Figure figure = Figure(Figure::Type::QUARTER),
        AlterationPreference pref = AlterationPreference::SHARP
    );

    // ------------------------------------------------------------
    // Create from char (notation directe)
    // ------------------------------------------------------------
    static Note create(
        char name,
        Accidental accid,
        int8_t octave=4,
        Figure figure = Figure(Figure::Type::QUARTER)
    );

    // ------------------------------------------------------------
    // Create from Pitch
    // ------------------------------------------------------------
    static Note create(
        const Pitch& pitch,
        Figure figure,
        AlterationPreference pref = AlterationPreference::SHARP
    );
};

} // namespace musical::core::note