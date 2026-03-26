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
    return Chord(
        root,
        ChordTypeCatalog::get(type)
    );
}


// -----------------------------------------------------------------------------
// Création depuis une gamme (empilement de tierces)
// -----------------------------------------------------------------------------
Chord
Factory::create(
    const pitch_t& root,
    const musical::core::scale::ScaleKeyed& scale,
    uint8_t nb_notes)
{
    using I = Interval;

    if (scale.size() == 0)
        throw std::invalid_argument("Scale is empty");

    ChordType chordType;

    const int root_pc = static_cast<int>(chromatic_index(root));

    for (uint8_t i = 1; i < nb_notes; ++i)
    {
        // empilement de tierces → 1, 3, 5, 7, 9...
        const std::size_t degree =
            (i * 2) % scale.size();

        const pitch_t& note = scale[degree];

        int pc = static_cast<int>(chromatic_index(note));

        int semitones = pc - root_pc;
        semitones = (semitones + 12) % 12;

        chordType += static_cast<I>(semitones);
    }

    return Chord(root, chordType);
}
Chord Factory::create(
    const pitch_t& root,
    ChordType::IntervalMask mask)
{
    return Chord(root, ChordType(mask));
}

} // namespace musical::core::chord