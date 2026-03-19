#include <musical/io/guitar/unicode/MovableDiagram.h>

namespace io::guitar::unicode
{

namespace sst = chord::database;

MovableDiagram::MovableDiagram(const sst::MovableShapeDiagram& diagram)
:
GridCore(6, diagram.nb_case())
{
    using SS = sst::MovableShapeDiagram::string_state;

    const auto& strings = diagram.strings();

    std::size_t first_fret = diagram.first_case();

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
                static_cast<GridCore::STRING>(s),
                relative_fret,
                static_cast<GridCore::DOIGT>(sp.finger()));
        }
    }
}

}