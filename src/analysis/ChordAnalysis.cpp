#include <musical/analysis/ChordAnalysis.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/intervals_defs.h>

#include <algorithm>

namespace musical::analysis::Chord {

using IT = musical::core::IntervalType;

bool is_minor(const core::Chord& chord)
{
    const auto& iv = chord.intervals();

    return std::find(iv.begin(), iv.end(), IT::TIERCE_MINEURE) != iv.end();
}

bool is_major(const core::Chord& chord)
{
    const auto& iv = chord.intervals();

    return std::find(iv.begin(), iv.end(), IT::TIERCE_MAJEURE) != iv.end();
}

bool has_seventh(const core::Chord& chord)
{
    const auto& iv = chord.intervals();

    return std::find(iv.begin(), iv.end(), IT::SEPTIEME_MINEURE) != iv.end()
        || std::find(iv.begin(), iv.end(), IT::SEPTIEME_MAJEURE) != iv.end();
}

} // namespace musical::analysis::Chord
