#include <musical/Core/chord/Factory.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/ChordTypeCatalog.h>
#include <musical/Core/pitch_t.h>

#include <stdexcept>

namespace musical::core::chord {

// -----------------------------------------------------------------------------
// Création depuis un type d'accord standard
// -----------------------------------------------------------------------------
Chord 
Factory::create(
    const pitch_t& root,
    ChordTypeCatalog::StandardChord type)
{
    const ChordType& chordType =
        ChordTypeCatalog::get(type);

    return Chord(root, chordType);
}


// -----------------------------------------------------------------------------
// Création depuis une gamme (empilement de tierces)
// -----------------------------------------------------------------------------
Chord
Factory::create(
    const pitch_t& root,
    const musical::core::scale::ScaleKeyed& scale,
    ChordClassType nb_notes)
{
    std::vector<IntervalType> intervals;

    int root_pc = static_cast<int>(chromatic_index(root));

    for (int i = 1; i < static_cast<int>(nb_notes); ++i)
    {
        int degree = i * 2;
        const pitch_t& n = scale[degree % scale.size()];

        int pc = static_cast<int>(chromatic_index(n));
        int semitones = pc - root_pc;

        if (semitones < 0)
            semitones += 12;

        intervals.push_back(
            static_cast<IntervalType>(semitones)
        );
    }

    return Chord(root, ChordType(intervals));
}

} // namespace musical::core::chord