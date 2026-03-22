#include <musical/analysis/ChordAnalysis.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/Intervals.h>

namespace musical::analysis::chord
{

using musical::core::Interval;
using musical::core::chord::Chord;

// ------------------------------------------------------------
// Qualité triadique
// ------------------------------------------------------------

bool is_minor(const Chord& chord)
{
    return chord.type().has(Interval::MINOR_THIRD);
}

bool is_major(const Chord& chord)
{
    return chord.type().has(Interval::MAJOR_THIRD);
}

// ------------------------------------------------------------
// Extensions
// ------------------------------------------------------------

bool has_seventh(const Chord& chord)
{
    const auto& t = chord.type();

    return t.has(Interval::MINOR_SEVENTH) ||
           t.has(Interval::MAJOR_SEVENTH);
}

} // namespace musical::analysis::chord