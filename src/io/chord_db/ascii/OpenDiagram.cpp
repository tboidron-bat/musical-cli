#include <musical/io/chord_db/ascii/OpenDiagram.h>

#include <string>
#include <vector>

namespace chord::db {

//static constexpr const char* STRING_CHAR = "\xE2\x94\x82"; // │

static constexpr const char* STRING_CHAR = "│";
static constexpr const char* EMPTY_CELL  = ".";
//static constexpr const char* EMPTY_CELL = "─";


static const char* CIRCLED_DIGITS[] =
{
    "", "❶", "❷", "❸", "❹",
    "❺", "❻", "❼", "❽", "❾"
};

static const char* circled_digits[] =
{
    "", "①", "②", "③", "④",
    "⑤", "⑥", "⑦", "⑧", "⑨"
};

static std::string to_roman(uint8_t value)
{
    static const std::pair<uint8_t, const char*> romans[] = {
        {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}
    };

    std::string result;
    for (auto& [v, s] : romans)
    {
        while (value >= v)
        {
            result += s;
            value -= v;
        }
    }
    return result;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
static void draw_open_strings(
    std::ostream& os,
    const OpenChordDiagram& diagram)
{
    const auto& strings = diagram.strings();
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    for (std::size_t s = 0; s < N; ++s)
    {
        const auto& sp = strings[s];

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

static void draw_fingers(
    std::vector<std::vector<char>>& grid,
    const OpenChordDiagram& diagram)
{
    using SS = OpenChordDiagram::string_state;

    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    std::size_t first_fret = diagram.first_case();
    std::size_t height     = diagram.nb_case();

    const auto& strings = diagram.strings();

    for (std::size_t s = 0; s < N; ++s)
    {
        const auto& sp = strings[s];

        if (sp.state() == SS::State::FRETTED)
        {
            std::size_t fret = sp.fret();

            if (fret >= first_fret)
            {
                std::size_t row = fret - first_fret;

                if (row < height)
                {
                    grid[row][s] =
                        static_cast<char>('0' + sp.finger());
                }
            }
        }
    }
}

// ------------------------------------------------------------

static std::vector<std::vector<char>>
make_grid(const OpenChordDiagram& diagram)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    std::size_t height = diagram.nb_case();

    std::vector<std::vector<char>> grid(
        height,
        std::vector<char>(N, '|')
    );

    draw_fingers(grid, diagram);

    return grid;
}
// ------------------------------------------------------------
static void draw_first_fret_label(
    std::ostream& os,
    const OpenChordDiagram& diagram)
{
    std::size_t first = diagram.first_case();

    if (first <= 4)
        return;

    constexpr auto N = OpenChordDiagram::STRING_COUNT;
    constexpr std::size_t width = N * 2 - 1;

    os << to_roman(first);
}

// ------------------------------------------------------------
static void render_grid(
    std::ostream& os,
    const std::vector<std::vector<char>>& grid,
    const OpenChordDiagram& diagram)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    for (std::size_t row = 0; row < grid.size(); ++row)
    {
        for (std::size_t s = 0; s < N; ++s)
        {
            char c = grid[row][s];

            if (c == '|')
                os << STRING_CHAR;
            else
                os << c;

            if (s != N - 1)
                os << EMPTY_CELL;
        }

        if (row == 0)
            draw_first_fret_label(os, diagram);

        os << '\n';
    }
}
// ------------------------------------------------------------
std::ostream& draw_nut(std::ostream& os, uint8_t string_count)
{
    os << std::string(string_count * 2 - 1, '=') << '\n';
    return os;
}
// ------------------------------------------------------------

static std::size_t draw_missing_frets_before(
    std::ostream& os,
    const OpenChordDiagram& diagram)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    std::size_t first = diagram.first_case();

    if (first <= 1)
        return 0;

    std::size_t missing = first - 1;

    for (std::size_t i = 0; i < missing; ++i)
    {
        for (std::size_t s = 0; s < N; ++s)
            if (s == N - 1)
                os << STRING_CHAR;
            else
                os << STRING_CHAR << EMPTY_CELL;

        os << '\n';
    }

    return missing;
}
static void draw_padding_frets(
    std::ostream& os,
    std::size_t n)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t s = 0; s < N; ++s)
            if (s == N - 1)
                os << STRING_CHAR;
            else
                os << STRING_CHAR << EMPTY_CELL;

        os << '\n';
    }
}
// ------------------------------------------------------------
static void draw_dots(std::ostream& os)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    constexpr std::size_t width = N * 2 - 1;
    constexpr std::size_t center = width / 2;

    for (int i = 0; i < 3; ++i)
        os << std::string(center, ' ') << ".\n";
}
// ------------------------------------------------------------

std::ostream& operator<<(
    std::ostream& os,
    const OpenChordDiagram& diagram)
{
    constexpr auto N = OpenChordDiagram::STRING_COUNT;

    constexpr std::size_t DEFAULT_DIAGRAM_HEIGHT = 4;

    draw_open_strings(os, diagram);

    draw_nut(os, N);

    auto grid = make_grid(diagram);

    if(diagram.first_case() <= 4){

        std::size_t before = draw_missing_frets_before(os, diagram);

        render_grid(os, grid, diagram);

        std::size_t after =
            DEFAULT_DIAGRAM_HEIGHT - (before + grid.size());

        draw_padding_frets(os, after);
    }
    else{

        draw_dots(os);    
        render_grid(os, grid, diagram);   
    }

    return os;
}

}