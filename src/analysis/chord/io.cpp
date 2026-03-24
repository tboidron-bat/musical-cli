#include <musical/analysis/chord/io.h>
#include <musical/Core/chord/ChordType.h>

namespace musical::analysis::chord
{

using IT = musical::core::Interval;
using CT = musical::core::chord::ChordType;

// helper
static bool has_all(const CT& c, std::initializer_list<IT> list)
{
    for (auto i : list)
        if (!c.has(i))
            return false;
    return true;
}

// ============================================================
// CHORD TYPE → STREAM
// ============================================================
std::ostream& operator<<(std::ostream& os, const CT& c)
{
    // ========================================================
    // TETRADES (prioritaires)
    // ========================================================

    if (has_all(c, {
            IT::MAJOR_THIRD,
            IT::PERFECT_FIFTH,
            IT::MINOR_SEVENTH }))
        return os << "7";

    if (has_all(c, {
            IT::MAJOR_THIRD,
            IT::PERFECT_FIFTH,
            IT::MAJOR_SEVENTH }))
        return os << "maj7";

    if (has_all(c, {
            IT::MINOR_THIRD,
            IT::PERFECT_FIFTH,
            IT::MINOR_SEVENTH }))
        return os << "m7";

    if (has_all(c, {
            IT::MINOR_THIRD,
            IT::TRITONE,
            IT::MINOR_SEVENTH }))
        return os << "m7b5";

    if (has_all(c, {
            IT::MINOR_THIRD,
            IT::TRITONE,
            IT::MAJOR_SIXTH }))
        return os << "dim7";

    // ========================================================
    // TRIADES
    // ========================================================

    if (has_all(c, { IT::MAJOR_THIRD, IT::PERFECT_FIFTH }))
        return os << "maj";

    if (has_all(c, { IT::MINOR_THIRD, IT::PERFECT_FIFTH }))
        return os << "min";

    if (has_all(c, { IT::MINOR_THIRD, IT::TRITONE }))
        return os << "dim";

    // ⚠️ théorique : devrait être AUGMENTED_FIFTH
    if (has_all(c, { IT::MAJOR_THIRD, IT::MINOR_SIXTH }))
        return os << "aug";

    // ========================================================
    // SUS
    // ========================================================

    if (has_all(c, {
            IT::PERFECT_FOURTH,
            IT::PERFECT_FIFTH }))
        return os << "sus4";

    if (has_all(c, {
            IT::MAJOR_SECOND,
            IT::PERFECT_FIFTH }))
        return os << "sus2";

    // ========================================================
    // ADD
    // ========================================================

    if (has_all(c, {
            IT::MAJOR_THIRD,
            IT::PERFECT_FIFTH,
            IT::MAJOR_SECOND }))
        return os << "add2";

    if (has_all(c, {
            IT::MAJOR_THIRD,
            IT::PERFECT_FIFTH,
            IT::PERFECT_FOURTH }))
        return os << "add4";

    return os << "unknown";
}

} // namespace musical::analysis::chord