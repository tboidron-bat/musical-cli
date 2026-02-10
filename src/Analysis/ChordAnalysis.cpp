#include <musical/Analysis/ChordAnalysis.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/MusicalCoreEnums.h>

#include <algorithm>

namespace musical::Analysis::Chord {

using IT = musical::IntervalType;

bool is_minor(const musical::Chord& chord)
{
    const auto& iv = chord.intervals();

    return std::find(iv.begin(), iv.end(), IT::TIERCE_MINEURE) != iv.end();
}

bool is_major(const musical::Chord& chord)
{
    const auto& iv = chord.intervals();

    return std::find(iv.begin(), iv.end(), IT::TIERCE_MAJEURE) != iv.end();
}

bool has_seventh(const musical::Chord& chord)
{
    const auto& iv = chord.intervals();

    return std::find(iv.begin(), iv.end(), IT::SEPTIEME_MINEURE) != iv.end()
        || std::find(iv.begin(), iv.end(), IT::SEPTIEME_MAJEURE) != iv.end();
}

} // namespace musical::Analysis::Chord
