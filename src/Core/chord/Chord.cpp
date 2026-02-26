#include <musical/Core/chord/Chord.h>
#include <musical/Core/pitch_t.h>

namespace musical::core::chord {

std::size_t Chord::size() const
{
    return 1 + _type.size();
}


// ------------------------------------------------------------
// Génération des notes de l'accord
// ------------------------------------------------------------
std::vector<pitch_t> Chord::notes(bool with_sharp) const
{
    std::vector<pitch_t> result;

    int root_pc = static_cast<int>(chromatic_index(_tonic));
    int octave  = _tonic._octave;

    // Ajouter la tonique
    result.push_back(_tonic);

    // Ajouter les autres notes via les intervalles
    for (IntervalType interval : _type.intervals())
    {
        int semitone = root_pc + static_cast<int>(interval);
        pitch_t p = pitch_from_chromatic_index(semitone, with_sharp);
        p._octave = octave;

        result.push_back(p);
    }

    return result;
}

} // namespace musical::core::chord