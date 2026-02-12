#include <musical/Core/chord/Factory.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/common.h>
#include <musical/Core/note/Note.h>
#include <musical/io/chord/parser.h>

#include <stdexcept>
#include <map>

namespace musical::core::chord {

// -----------------------------------------------------------------------------
// Création depuis un type d'accord standard
// -----------------------------------------------------------------------------
Chord 
Factory::create(const Note& root, CommonType type)
{
    auto it = common_chord().find(type);

    if (it == common_chord().end())
        throw std::invalid_argument("Unknown CommonType");

    return Chord(root, it->second);
}


// -----------------------------------------------------------------------------
// Création depuis une gamme (empilement de tierces)
// -----------------------------------------------------------------------------
Chord
Factory::create(
    const Note& root,
    const musical::core::scale::ScaleKeyed& scale,
    ChordClassType nb_notes)
{
    std::vector<IntervalType> intervals;

    int root_pc = root.chromatic_index();

    for (int i = 1; i < static_cast<int>(nb_notes); ++i)
    {
        int degree = i * 2;
        const Note& n = scale[degree % scale.size()];

        int pc = n.chromatic_index();
        int semitones = pc - root_pc;

        if (semitones < 0)
            semitones += 12;

        intervals.push_back(interval_from_semitones(semitones));
    }

    return Chord(root, intervals);
}
} // namespace musical
