#include <musical/io/guitar/unicode/OpenDiagram.h>

namespace io::guitar::unicode
{

using namespace chord::database;

static constexpr std::size_t DEFAULT_DIAGRAM_HEIGHT = 4;

static std::size_t compute_total_cases(
    const chord::database::OpenChordDiagram& diagram)
{
    constexpr std::size_t DEFAULT_DIAGRAM_HEIGHT = 4;

    std::size_t first = diagram.first_fret();

    std::size_t missing_before =
        (first > 1) ? first - 1 : 0;

    std::size_t visible =
        diagram.nb_frets();

    std::size_t padding_after =
        (missing_before + visible < DEFAULT_DIAGRAM_HEIGHT)
        ? DEFAULT_DIAGRAM_HEIGHT - (missing_before + visible)
        : 0;

    return missing_before + visible + padding_after;
}

OpenDiagram::OpenDiagram(
    const chord::database::OpenChordDiagram&diagram)
:
Grid(
    chord::database::OpenChordDiagram::STRING_COUNT,
    compute_total_cases(diagram),
    true
)
{
    using SS = chord::database::OpenChordDiagram::string_state;

    const auto& strings = diagram.strings();

    std::size_t first_fret = diagram.first_fret();
    std::size_t missing = (first_fret > 1) ? first_fret - 1 : 0;

    for(std::size_t s = 0; s < SixStringDiagram::STRING_COUNT; ++s)
    {
        const auto& sp = strings[s];

        Grid::STRING string =
            static_cast<Grid::STRING>(s);

        switch(sp.state())
        {
            case SS::State::OPEN_STRING:
                set_open_string(string);
                break;

            case SS::State::MUTED:
                set_muted_string(string);
                break;

            case SS::State::FRETTED:
            {
                std::size_t fret = sp.fret();

                if(fret >= first_fret)
                {
                    std::size_t row =
                        (fret - first_fret) + missing;

                    set_finger(
                        string,
                        row,
                        static_cast<Grid::DOIGT>(sp.finger())
                    );
                }
                break;
            }

            default:
                break;
        }
    }
}
}