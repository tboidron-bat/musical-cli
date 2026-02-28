#include <musical/io/instruments/guitar/six_strings/movable_chord_diagram_to_ascii.h>

#include <musical/instruments/guitar/six_strings/MovableShapeDiagram.h>

#include <sstream>
#include <algorithm>

namespace io::guitar::six_strings {

    namespace sst = musical::instruments::guitar::six_strings;

// ------------------------------------------------------------------
// Rendu ASCII depuis un MovableShapeDiagram
// ------------------------------------------------------------------

std::string movable_chord_diagram_to_ascii(const sst::MovableShapeDiagram& diagram)
{
    using D  = sst::MovableShapeDiagram;
    using SS = sst::MovableShapeDiagram::string_state;

    const auto& strings = diagram.strings();

    std::size_t height = diagram.nb_frets();
    if (height == 0)
        height = 1;

    std::ostringstream oss;

    // ------------------------------------------------------------
    // Ligne muted / unused
    // ------------------------------------------------------------
    for (const auto& sp : strings)
    {
        if (sp.state() == SS::State::MUTED)
            oss << "x ";
        else
            oss << "  ";
    }
    oss << '\n';

    oss << std::string(D::STRING_COUNT * 2 - 1, '-') << '\n';

    // ------------------------------------------------------------
    // Corps : offsets relatifs
    // ------------------------------------------------------------
    for (std::size_t row = 0; row < height; ++row)
    {
        std::size_t current_offset = row + 1; // 1 = base fret

        for (const auto& sp : strings)
        {
            if (sp.state() == SS::State::FRETTED_OFFSET &&
                sp.offset() == current_offset)
            {
                oss << static_cast<char>('0' + sp.finger()) << ' ';
            }
            else
            {
                oss << "| ";
            }
        }

        oss << '\n';
    }

    return oss.str();
}

} // namespace io::guitar::six_strings