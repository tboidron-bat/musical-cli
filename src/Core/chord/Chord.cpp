#include <musical/Core/chord/Chord.h>
#include <musical/Core/pitch_t.h>

namespace musical::core::chord {

std::size_t Chord::size() const
{
    return 1 + _type.size();
}
std::vector<pitch_t> 
Chord::notes(bool with_sharp) const
{
    std::vector<pitch_t> result;

    int root_pc = static_cast<int>(chromatic_index(_tonic));
    int base_octave = _tonic.octave();

    // Tonique
    result.push_back(_tonic);

    auto mask = _type.intervals_mask();

    // Parcours des 64 bits
    for (uint8_t i = 0; i < 64; ++i)
    {
        if (!(mask & (1ULL << i)))
            continue;

        int semitone = root_pc + i;

        pitch_t p = pitch_from_chromatic_index(semitone, with_sharp);

        // Gestion octave correcte
        p._octave = base_octave + (semitone / 12);

        result.push_back(p);
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const Chord& chord)
{
    os << chord.root()
       << " "
       << chord.type();

    return os;
}

} // namespace musical::core::chord