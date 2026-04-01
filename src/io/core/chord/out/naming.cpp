
#include <musical/io/core/chord/out/naming.h>

#include <musical/core/chord/ChordType.h>

#include <string>
#include <initializer_list>

namespace musical::io::chord
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
// CHORD TYPE → NAME //TODO :: ajouter les altérations, extensions, etc.
// ============================================================
std::string to_string(const CT& c)
{
    // ========================
    // TETRADES
    // ========================

    if (has_all(c, { IT::MAJOR_THIRD, IT::PERFECT_FIFTH, IT::MINOR_SEVENTH }))
        return "7";

    if (has_all(c, { IT::MAJOR_THIRD, IT::PERFECT_FIFTH, IT::MAJOR_SEVENTH }))
        return "maj7";

    if (has_all(c, { IT::MINOR_THIRD, IT::PERFECT_FIFTH, IT::MINOR_SEVENTH }))
        return "m7";

    if (has_all(c, { IT::MINOR_THIRD, IT::TRITONE, IT::MINOR_SEVENTH }))
        return "m7b5";

    if (has_all(c, { IT::MINOR_THIRD, IT::TRITONE, IT::MAJOR_SIXTH }))
        return "dim7";

    // ========================
    // TRIADES
    // ========================

    if (has_all(c, { IT::MAJOR_THIRD, IT::PERFECT_FIFTH }))
        return "maj";

    if (has_all(c, { IT::MINOR_THIRD, IT::PERFECT_FIFTH }))
        return "min";

    if (has_all(c, { IT::MINOR_THIRD, IT::TRITONE }))
        return "dim";

    if (has_all(c, { IT::MAJOR_THIRD, IT::MINOR_SIXTH }))
        return "aug";

    // ========================
    // SUS
    // ========================

    if (has_all(c, { IT::PERFECT_FOURTH, IT::PERFECT_FIFTH }))
        return "sus4";

    if (has_all(c, { IT::MAJOR_SECOND, IT::PERFECT_FIFTH }))
        return "sus2";

    // ========================
    // ADD
    // ========================

    if (has_all(c, { IT::MAJOR_THIRD, IT::PERFECT_FIFTH, IT::MAJOR_SECOND }))
        return "add2";

    if (has_all(c, { IT::MAJOR_THIRD, IT::PERFECT_FIFTH, IT::PERFECT_FOURTH }))
        return "add4";

    return "unknown";
}std::ostream& operator<<(std::ostream& os, const musical::core::chord::ChordType& c)
{
    return os << to_string(c);
}
} // namespace musical::io::chord

