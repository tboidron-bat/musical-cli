#include <musical/analysis/ChordAnalysis.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/intervals_defs.h>

#include <algorithm>

namespace musical::analysis::chord
{

using musical::core::IntervalType;
using musical::core::chord::Chord;

bool is_minor(const Chord& chord)
{
    const auto& iv = chord.type().intervals();

    return std::find(iv.begin(), iv.end(),
                     IntervalType::TIERCE_MINEURE) != iv.end();
}

bool is_major(const Chord& chord)
{
    const auto& iv = chord.type().intervals();

    return std::find(iv.begin(), iv.end(),
                     IntervalType::TIERCE_MAJEURE) != iv.end();
}

bool has_seventh(const Chord& chord)
{
    const auto& iv = chord.type().intervals();

    return std::find(iv.begin(), iv.end(),
                     IntervalType::SEPTIEME_MINEURE) != iv.end()
        || std::find(iv.begin(), iv.end(),
                     IntervalType::SEPTIEME_MAJEURE) != iv.end();
}

} // namespace musical::analysis::chord