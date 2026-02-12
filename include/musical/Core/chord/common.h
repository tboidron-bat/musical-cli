#pragma once

#include <map>
#include <vector>
#include <stdexcept>

#include <musical/Core/intervals_defs.h>

namespace musical::core::chord
{

// -----------------------------------------------------------------------------
// Type d'accord commun (catalogue fixe)
// -----------------------------------------------------------------------------
enum class CommonType
{
    // --- Triades ---
    MAJOR,
    MINOR,
    DIMINISHED,
    AUGMENTED,

    // --- 7 ---
    MAJOR7,
    DOMINANT7,
    MINOR7,
    HALF_DIMINISHED7,
    DIMINISHED7,

    // --- 9 ---
    MAJOR9,
    DOMINANT9,
    MINOR9,

    // --- 11 ---
    MAJOR11,
    DOMINANT11,
    MINOR11,

    // --- 13 ---
    MAJOR13,
    DOMINANT13,
    MINOR13,

    // --- Altérés ---
    DOMINANT7_FLAT5,
    DOMINANT7_SHARP5,
    DOMINANT7_FLAT9,
    DOMINANT7_SHARP9,

    // --- Autres ---
    SUSPENDED2,
    SUSPENDED4,
    ADD9,
    MAJOR6,
    MINOR6,

    NOCHORD,
    UNKNOWN
};

// Alias pratique
using IT = IntervalType;

// -----------------------------------------------------------------------------
// Conversion sécurisée demi-tons -> IntervalType
// -----------------------------------------------------------------------------
inline IntervalType interval_from_semitones(int semitones)
{
    if (semitones < 0 ||
        semitones > static_cast<int>(IntervalType::DOUBLE_OCTAVE))
    {
        throw std::invalid_argument("Invalid semitone value for IntervalType");
    }

    return static_cast<IntervalType>(semitones);
}

// -----------------------------------------------------------------------------
// Table des intervalles par type d'accord
// -----------------------------------------------------------------------------
inline const std::map<CommonType, std::vector<IT>>& common_chord()
{
    static const std::map<CommonType, std::vector<IT>> table =
    {
        // --- Triades ---
        { CommonType::MAJOR,            { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE } },
        { CommonType::MINOR,            { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE } },
        { CommonType::DIMINISHED,       { IT::TIERCE_MINEURE, IT::TRITON } },
        { CommonType::AUGMENTED,        { IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE } },

        // --- 7 ---
        { CommonType::DOMINANT7,        { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE } },
        { CommonType::MAJOR7,           { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE } },
        { CommonType::MINOR7,           { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE } },
        { CommonType::HALF_DIMINISHED7, { IT::TIERCE_MINEURE, IT::TRITON, IT::SEPTIEME_MINEURE } },
        { CommonType::DIMINISHED7,      { IT::TIERCE_MINEURE, IT::TRITON, IT::SIXTE_MAJEURE } },

        // --- 9 ---
        { CommonType::MAJOR9,           { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE } },
        { CommonType::DOMINANT9,        { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE } },
        { CommonType::MINOR9,           { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE } },

        // --- 11 ---
        { CommonType::MAJOR11,          { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME } },
        { CommonType::DOMINANT11,       { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME } },
        { CommonType::MINOR11,          { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME } },

        // --- 13 ---
        { CommonType::MAJOR13,          { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME, IT::TREIZIEME_MAJEURE } },
        { CommonType::DOMINANT13,       { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME, IT::TREIZIEME_MAJEURE } },
        { CommonType::MINOR13,          { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME, IT::TREIZIEME_MAJEURE } },

        // --- Suspensions ---
        { CommonType::SUSPENDED2,       { IT::SECONDE_MAJEURE, IT::QUINTE_JUSTE } },
        { CommonType::SUSPENDED4,       { IT::QUARTE_JUSTE, IT::QUINTE_JUSTE } },

        // --- Add ---
        { CommonType::ADD9,             { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::NEUVIEME_MAJEURE } },

        // --- Sixte ---
        { CommonType::MAJOR6,           { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SIXTE_MAJEURE } },
        { CommonType::MINOR6,           { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SIXTE_MAJEURE } },

        { CommonType::NOCHORD,          {} },
        { CommonType::UNKNOWN,          {} }
    };

    return table;
}

} // namespace musical::core::chord
