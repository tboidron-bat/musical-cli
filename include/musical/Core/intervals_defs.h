#pragma once

#include <cstdint>

namespace musical::core {

    enum class IntervalType : uint8_t {

        TONIQUE = 0,
        SECONDE_MINEURE = 1,
        SECONDE_MAJEURE = 2,
        TIERCE_MINEURE = 3,
        TIERCE_MAJEURE = 4,
        QUARTE_JUSTE = 5,
        TRITON = 6,
        QUINTE_JUSTE = 7,
        SIXTE_MINEURE = 8,
        SIXTE_MAJEURE = 9,
        SEPTIEME_MINEURE = 10,
        SEPTIEME_MAJEURE = 11,
        OCTAVE = 12,
        
        // Au-delà de l'octave (douzième, treizième, etc.)
        NEUVIEME_MINEURE = 13,  // octave + seconde mineure
        NEUVIEME_MAJEURE = 14,  // octave + seconde majeure
        DIXIEME_MINEURE = 15,   // octave + tierce mineure
        DIXIEME_MAJEURE = 16,   // octave + tierce majeure
        ONZIEME = 17,           // octave + quarte juste
        ONZIEME_AUGMENTEE = 18, // octave + triton
        DOUZIEME = 19,          // octave + quinte juste
        TREIZIEME_MINEURE = 20, // octave + sixte mineure
        TREIZIEME_MAJEURE = 21, // octave + sixte majeure
        QUATORZIEME_MINEURE = 22, // octave + septième mineure
        QUATORZIEME_MAJEURE = 23, // octave + septième majeure
        DOUBLE_OCTAVE = 24       // 2 octaves
    };
}


