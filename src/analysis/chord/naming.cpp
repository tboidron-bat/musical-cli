#include <musical/analysis/chord/naming.h>
#include <musical/Core/chord/ChordType.h> 

//#include <musical/Core/intervals_defs.h>

#include <vector>

namespace musical::analysis::chord
{

using IT = musical::core::IntervalType;

// helper pour éviter les répétitions
static bool equals(
    const std::vector<IT>& a,
    std::initializer_list<IT> b)
{
    return a.size() == b.size()
        && std::equal(a.begin(), a.end(), b.begin());
}

// ============================================================
// CHORD TYPE → STRING
// ============================================================
std::string find_name(
    const musical::core::chord::ChordType& type)
{
    const auto& iv = type.intervals();

    // TRIADES
    if (equals(iv, { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }))
        return "maj";

    if (equals(iv, { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }))
        return "min";

    if (equals(iv, { IT::TIERCE_MINEURE, IT::TRITON }))
        return "dim";

    if (equals(iv, { IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE }))
        return "aug";

    // TETRADES
    if (equals(iv, {
            IT::TIERCE_MAJEURE,
            IT::QUINTE_JUSTE,
            IT::SEPTIEME_MINEURE }))
        return "maj:7";

    if (equals(iv, {
            IT::TIERCE_MAJEURE,
            IT::QUINTE_JUSTE,
            IT::SEPTIEME_MAJEURE }))
        return "maj:7M";

    if (equals(iv, {
            IT::TIERCE_MINEURE,
            IT::QUINTE_JUSTE,
            IT::SEPTIEME_MINEURE }))
        return "min:7";

    if (equals(iv, {
            IT::TIERCE_MINEURE,
            IT::TRITON,
            IT::SEPTIEME_MINEURE }))
        return "min:7:b5";

    if (equals(iv, {
            IT::TIERCE_MINEURE,
            IT::TRITON,
            IT::SIXTE_MAJEURE }))
        return "dim7";

    // SUS
    if (equals(iv, {
            IT::QUARTE_JUSTE,
            IT::QUINTE_JUSTE }))
        return "sus4";

    if (equals(iv, {
            IT::SECONDE_MAJEURE,
            IT::QUINTE_JUSTE }))
        return "sus2";

    // ADD
    if (equals(iv, {
            IT::TIERCE_MAJEURE,
            IT::QUINTE_JUSTE,
            IT::SECONDE_MAJEURE }))
        return "add2";

    if (equals(iv, {
            IT::TIERCE_MAJEURE,
            IT::QUINTE_JUSTE,
            IT::QUARTE_JUSTE }))
        return "add4";

    return "unknown";
}

} // namespace musical::analysis::chord