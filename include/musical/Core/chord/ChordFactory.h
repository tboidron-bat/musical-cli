#pragma once

#include <cstdint>

#include <musical/Core/Pitch.h>
#include <musical/Core/chord/ChordType.h>
#include <musical/Core/chord/ChordTypeCatalog.h>


namespace musical::core::chord {
    class Chord;
}
namespace musical::core::scale {
    class ScaleKeyed;
}

namespace musical::core::chord {

class ChordFactory {

public:

    // ------------------------------------------------------------
    // Création depuis un type d'accord standard
    // ------------------------------------------------------------
    static Chord create(
        const Pitch& root,
        ChordTypeCatalog::StandardChord type
    );

    // ------------------------------------------------------------
    // Crée un accord diatonique (triade, tétrade, etc.)
    // à partir d’une gamme
    // ------------------------------------------------------------
    static Chord create(
        const Pitch& root,
        const musical::core::scale::ScaleKeyed& gamme,
        uint8_t nb_note = 3
    );

    // ------------------------------------------------------------
    // Création directe via mask d’intervalles
    // ------------------------------------------------------------
    static Chord create(
        const Pitch& root,
        ChordType::IntervalMask mask
    );

};

} // namespace musical::core::chord