#pragma once

#include <string>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/ChordTypeCatalog.h>
#include <musical/Core/scale/ScaleKeyed.h>

namespace musical::core::chord {

class Factory {

public:

    // ------------------------------------------------------------
    // Création depuis un type d'accord standard
    // ------------------------------------------------------------
    static Chord create(
        const pitch_t& root,
        ChordTypeCatalog::StandardChord type
    );

    // ------------------------------------------------------------
    // Crée un accord diatonique (dyade, triade, etc.)
    // à partir d’une gamme
    // ------------------------------------------------------------
    static Chord create(
        const pitch_t& root,
        const musical::core::scale::ScaleKeyed& gamme,
        uint8_t nb_note = 3
    );
};

} // namespace musical::core::chord