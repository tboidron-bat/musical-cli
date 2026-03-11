#include <musical/io/guitar/stream_diagram2.h>
#include <musical/instruments/guitar/six_strings/OpenChordDiagram.h>

#include <vector>
#include <ostream>

namespace musical::instruments::guitar::six_strings {

static constexpr const char* STRING = "│";
static constexpr const char* DOT    = "●";


// ------------------------------------------------------------
static void draw_open_strings(
    std::ostream& os,
    const OpenChordDiagram& diagram)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    for (size_t s = 0; s < N; ++s)
    {
        const auto& sp = diagram.strings()[s];

        if (sp.state() == OpenChordDiagram::string_state::State::OPEN_STRING)
            os << "o ";
        else if (sp.state() == OpenChordDiagram::string_state::State::MUTED)
            os << "× ";
        else
            os << "  ";
    }

    os << '\n';
}


// ------------------------------------------------------------
static std::vector<std::vector<char>>
make_grid(const OpenChordDiagram& diagram)
{
    using SS = OpenChordDiagram::string_state;

    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    size_t first_fret = diagram.first_fret();
    size_t height     = diagram.nb_frets();

    const auto& strings = diagram.strings();

    std::vector<std::vector<char>> grid(
        height,
        std::vector<char>(N, ' ')
    );

    for (size_t s = 0; s < N; ++s)
    {
        const auto& sp = strings[s];

        if (sp.state() == SS::State::FRETTED)
        {
            size_t fret = sp.fret();

            if (fret >= first_fret)
            {
                size_t row = fret - first_fret;

                if (row < height)
                    grid[row][s] = 'o';
            }
        }
    }

    return grid;
}


// ------------------------------------------------------------
static void draw_string_row(
    std::ostream& os,
    const std::vector<char>& row)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    for (size_t s = 0; s < N; ++s)
    {
        os << STRING;

        if (row[s] == 'o')
            os << DOT;
        else
            os << " ";
    }

    os << STRING << '\n';
}


// ------------------------------------------------------------
static void draw_fret_line(std::ostream& os)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    os << "├";

    for (size_t i = 0; i < N - 1; ++i)
        os << "─┼";

    os << "─┤\n";
}




// ------------------------------------------------------------
std::ostream& operator<<(
    std::ostream& os,
    const OpenChordDiagram& diagram)
{
    constexpr size_t HEIGHT = 4;
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    draw_open_strings(os, diagram);

    os << "╒═════════╕\n";

    auto grid = make_grid(diagram);

    for (size_t r = 0; r < HEIGHT; ++r)
    {
        if (r < grid.size())
            draw_string_row(os, grid[r]);
        else
            draw_string_row(os, std::vector<char>(N, ' '));

        if (r != HEIGHT - 1)
            draw_fret_line(os);
    }

    return os;
}

}