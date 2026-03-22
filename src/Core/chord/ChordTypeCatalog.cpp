#include <musical/Core/chord/ChordTypeCatalog.h>
#include <musical/Core/Intervals.h>

#include <stdexcept>

namespace musical::core::chord
{

const ChordType& ChordTypeCatalog::get(StandardChord type)
{
    auto index = static_cast<std::size_t>(type);

    if (index >= N)
        throw std::out_of_range("Invalid StandardChord");

    return TABLE[index];
}

// -----------------------------------------------------------------------------
// Table des types d'accords standards
// L'ordre DOIT correspondre exactement à l'enum StandardChord
// -----------------------------------------------------------------------------

using IT = Interval;

const std::array<ChordType, ChordTypeCatalog::N>
ChordTypeCatalog::TABLE =
{
    // --- Triades ---
    ChordType({ IT::MAJOR_THIRD, IT::PERFECT_FIFTH }),             // MAJOR
    ChordType({ IT::MINOR_THIRD, IT::PERFECT_FIFTH }),             // MINOR
    ChordType({ IT::MINOR_THIRD, IT::TRITONE }),                   // DIMINISHED
    ChordType({ IT::MAJOR_THIRD, IT::MINOR_SIXTH }),               // AUGMENTED

    // --- 7 ---
    ChordType({ IT::MAJOR_THIRD, IT::PERFECT_FIFTH, IT::MAJOR_SEVENTH }), // MAJOR7
    ChordType({ IT::MAJOR_THIRD, IT::PERFECT_FIFTH, IT::MINOR_SEVENTH }), // DOMINANT7
    ChordType({ IT::MINOR_THIRD, IT::PERFECT_FIFTH, IT::MINOR_SEVENTH }), // MINOR7
    ChordType({ IT::MINOR_THIRD, IT::TRITONE, IT::MINOR_SEVENTH }),       // HALF_DIMINISHED7
    ChordType({ IT::MINOR_THIRD, IT::TRITONE, IT::MAJOR_SIXTH }),         // DIMINISHED7

    // --- 9 ---
    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MAJOR_SEVENTH, IT::MAJOR_NINTH
    }), // MAJOR9

    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MAJOR_NINTH
    }), // DOMINANT9

    ChordType({
        IT::MINOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MAJOR_NINTH
    }), // MINOR9

    // --- 11 ---
    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MAJOR_SEVENTH, IT::MAJOR_NINTH,
        IT::PERFECT_ELEVENTH
    }), // MAJOR11

    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MAJOR_NINTH,
        IT::PERFECT_ELEVENTH
    }), // DOMINANT11

    ChordType({
        IT::MINOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MAJOR_NINTH,
        IT::PERFECT_ELEVENTH
    }), // MINOR11

    // --- 13 ---
    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MAJOR_SEVENTH, IT::MAJOR_NINTH,
        IT::PERFECT_ELEVENTH, IT::MAJOR_THIRTEENTH
    }), // MAJOR13

    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MAJOR_NINTH,
        IT::PERFECT_ELEVENTH, IT::MAJOR_THIRTEENTH
    }), // DOMINANT13

    ChordType({
        IT::MINOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MAJOR_NINTH,
        IT::PERFECT_ELEVENTH, IT::MAJOR_THIRTEENTH
    }), // MINOR13

    // --- Altérés ---
    ChordType({
        IT::MAJOR_THIRD, IT::TRITONE,
        IT::MINOR_SEVENTH
    }), // DOMINANT7b5

    ChordType({
        IT::MAJOR_THIRD, IT::MINOR_SIXTH,
        IT::MINOR_SEVENTH
    }), // DOMINANT7#5

    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MINOR_NINTH
    }), // DOMINANT7b9

    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MINOR_SEVENTH, IT::MINOR_TENTH
    }), // DOMINANT7#9

    // --- Suspensions / Add ---
    ChordType({ IT::MAJOR_SECOND, IT::PERFECT_FIFTH }),           // SUS2
    ChordType({ IT::PERFECT_FOURTH, IT::PERFECT_FIFTH }),         // SUS4

    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MAJOR_NINTH
    }), // ADD9

    // --- Sixte ---
    ChordType({
        IT::MAJOR_THIRD, IT::PERFECT_FIFTH,
        IT::MAJOR_SIXTH
    }), // MAJOR6

    ChordType({
        IT::MINOR_THIRD, IT::PERFECT_FIFTH,
        IT::MAJOR_SIXTH
    }) // MINOR6
};

} // namespace musical::core::chord