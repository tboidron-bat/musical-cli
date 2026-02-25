#pragma once

#include <array>
#include <cstddef>

#include <musical/Core/chord/ChordType.h>

namespace musical::core::chord
{

// -----------------------------------------------------------------------------
// Catalogue statique des types d'accords standards
// -----------------------------------------------------------------------------
class ChordTypeCatalog
{
public:
    enum class StandardChord
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

        COUNT
    };
private:
    static constexpr std::size_t N =
        static_cast<std::size_t>(StandardChord::COUNT);
public:
    /// Retourne le ChordType associé à un accord standard
    static const ChordType& get(StandardChord type);

private:
    static const std::array<ChordType, N> TABLE;
};

} // namespace musical::core::chord
