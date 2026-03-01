#include <musical/io/instruments/guitar/six_strings/movable_shape_diagram_to_ascii.h>
#include <musical/instruments/guitar/six_strings/MovableShapeDiagram.h>

#include <sstream>
#include <algorithm>

namespace io::guitar::six_strings {

namespace sst = musical::instruments::guitar::six_strings;

// ------------------------------------------------------------------
// Rendu ASCII depuis un MovableShapeDiagram
// ------------------------------------------------------------------

static std::string shape_to_string(sst::MovableShapeDiagram::CAGEDShape shape)
{
    switch (shape)
    {
        case sst::MovableShapeDiagram::CAGEDShape::C: return "C";
        case sst::MovableShapeDiagram::CAGEDShape::A: return "A";
        case sst::MovableShapeDiagram::CAGEDShape::G: return "G";
        case sst::MovableShapeDiagram::CAGEDShape::E: return "E";
        case sst::MovableShapeDiagram::CAGEDShape::D: return "D";
    }
    return "?";
}


std::string movable_shape_diagram_to_ascii(
    const sst::MovableShapeDiagram& diagram)
{
    using D  = sst::MovableShapeDiagram;
    using SS = sst::MovableShapeDiagram::string_state;

    const auto& strings = diagram.strings();

    std::size_t first_fret = diagram.first_fret();

    // if(first_fret == 0)
    //     return {};

    std::size_t height     = diagram.nb_frets();

    if (height == 0)
        height = 1;

    std::ostringstream oss;

    // ------------------------------------------------------------
    // Header : Shape
    // ------------------------------------------------------------
    oss << "[Shape "
        << shape_to_string(diagram.shape())
        << "]\n";

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

    // ------------------------------------------------------------
    // Corps : frettes réelles
    // ------------------------------------------------------------
    for (std::size_t row = 0; row < height; ++row)
    {
        std::size_t current_fret = first_fret + row;

        for (const auto& sp : strings)
        {
            if (sp.state() == SS::State::FRETTED_OFFSET)
            {
                std::size_t absolute_fret =
                    diagram.base_fret() + sp.offset();

                if (absolute_fret == current_fret)
                {
                    oss << static_cast<char>('0' + sp.finger()) << ' ';
                    continue;
                }
            }

            oss << "| ";
        }

        // 👉 Affichage uniquement sur la première ligne
        if (row == 0)
        {
            oss << "  frette " << current_fret;
        }

        oss << '\n';
    }

    return oss.str();
}

} // namespace io::guitar::six_strings