#include <musical/Core/chord/ChordTypeCatalog.h>
#include <musical/Core/intervals_defs.h>

#include <stdexcept>

namespace musical::core::chord
{
const ChordType& ChordTypeCatalog::get(StandardChord type)
{
    auto index = static_cast<std::size_t>(type);

    if (index >= N)
        throw std::out_of_range("Invalid StandardChord");    

    return TABLE[static_cast<std::size_t>(type)];
}
// -----------------------------------------------------------------------------
// Table des types d'accords standards
// L'ordre DOIT correspondre exactement à l'enum StandardChord
// -----------------------------------------------------------------------------
using IT = IntervalType;

const std::array<ChordType, ChordTypeCatalog::N>
ChordTypeCatalog::TABLE =
{
    // --- Triades ---
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }),                        // MAJOR
    ChordType({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }),                        // MINOR
    ChordType({ IT::TIERCE_MINEURE, IT::TRITON }),                              // DIMINISHED
    ChordType({ IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE }),                       // AUGMENTED

    // --- 7 ---
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }),  // MAJOR7
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }),  // DOMINANT7
    ChordType({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }),  // MINOR7
    ChordType({ IT::TIERCE_MINEURE, IT::TRITON, IT::SEPTIEME_MINEURE }),        // HALF_DIMINISHED7
    ChordType({ IT::TIERCE_MINEURE, IT::TRITON, IT::SIXTE_MAJEURE }),           // DIMINISHED7

    // --- 9 ---
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE }),                  // MAJOR9
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE }),                  // DOMINANT9
    ChordType({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE }),                  // MINOR9

    // --- 11 ---
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE,
                IT::ONZIEME }),                                                 // MAJOR11
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE,
                IT::ONZIEME }),                                                 // DOMINANT11
    ChordType({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE,
                IT::ONZIEME }),                                                 // MINOR11

    // --- 13 ---
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE,
                IT::ONZIEME, IT::TREIZIEME_MAJEURE }),                          // MAJOR13
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE,
                IT::ONZIEME, IT::TREIZIEME_MAJEURE }),                          // DOMINANT13
    ChordType({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE,
                IT::ONZIEME, IT::TREIZIEME_MAJEURE }),                          // MINOR13

    // --- Altérés ---
    ChordType({ IT::TIERCE_MAJEURE, IT::TRITON,
                IT::SEPTIEME_MINEURE }),                                        // DOMINANT7_FLAT5
    ChordType({ IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE,
                IT::SEPTIEME_MINEURE }),                                        // DOMINANT7_SHARP5
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::NEUVIEME_MINEURE }),                  // DOMINANT7_FLAT9
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SEPTIEME_MINEURE, IT::QUINZIEME }),                // DOMINANT7_SHARP9

    // --- Suspensions / Add ---
    ChordType({ IT::SECONDE_MAJEURE, IT::QUINTE_JUSTE }),                       // SUSPENDED2
    ChordType({ IT::QUARTE_JUSTE, IT::QUINTE_JUSTE }),                          // SUSPENDED4
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::NEUVIEME_MAJEURE }),                                         // ADD9

    // --- Sixte ---
    ChordType({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE,
                IT::SIXTE_MAJEURE }),                                            // MAJOR6
    ChordType({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE,
                IT::SIXTE_MAJEURE })                                             // MINOR6
};

} // namespace musical::core::chord
