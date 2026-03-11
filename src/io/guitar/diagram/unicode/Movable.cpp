#include <musical/io/guitar/diagram/unicode/Movable.h>

namespace io::guitar::diagram::unicode
{

namespace sst = musical::instruments::guitar::six_strings;

Movable::Movable(const sst::MovableShapeDiagram& diagram)
    :
    Grid(6, diagram.nb_frets(), diagram.first_fret() == 0)
{
    using SS = sst::MovableShapeDiagram::string_state;

    const auto& strings = diagram.strings();

    std::size_t first_fret = diagram.first_fret();

    for (std::size_t s = 0; s < strings.size(); ++s)
    {
        const auto& sp = strings[s];

        if (sp.state() == SS::State::FRETTED_OFFSET)
        {
            std::size_t absolute_fret =
                diagram.base_fret() + sp.offset();

            std::size_t relative_fret =
                absolute_fret - first_fret;

            set_finger(
                static_cast<Grid::STRING>(s),
                relative_fret,
                static_cast<Grid::DOIGT>(sp.finger()));
        }
    }
}

}