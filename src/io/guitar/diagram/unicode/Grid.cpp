#include <musical/io/guitar/diagram/unicode/Grid.h>

#include <sstream>

// const std::array<std::array<const char*, 11>, 4> base_diagram =
// {{
//     { "├","─","┼","─","┼","─","┼","─","┼","─","┤" },
//     { "├","─","┼","─","┼","─","┼","─","┼","─","┤" },
//     { "├","─","┼","─","┼","─","┼","─","┼","─","┤" },
//     { "├","─","┼","─","┼","─","┼","─","┼","─","┤" }
// }};    


namespace io::guitar::diagram::unicode
{

// static constexpr std::size_t CELL_BYTES =
//     std::char_traits<char>::length(FRET_BAR);

//
// ╒═════════╕
//    
void Grid::add_nut()
{
    std::size_t width = _grid[0].size();

    _grid[0][0] = NUT_LEFT;

    for (std::size_t i = 1; i < width - 1; ++i)
        _grid[0][i] = NUT_BAR;

    _grid[0][width - 1] = NUT_RIGHT;
}
//
//│ │ │ │ │ │
//
void Grid::add_strings(std::size_t row)
{
    std::size_t col = 0;

    for (std::size_t s = 0; s < _nb_strings; ++s)
    {
        _grid[row][col] = STRING_CHAR;

        if (s < _nb_strings - 1)
            col += 2;
    }
}
//
//├─┼─┼─┼─┼─┤
//
void Grid::add_fret(std::size_t row)
{
    std::size_t width = _grid[row].size();

    _grid[row][0] = FRET_LEFT;

    std::size_t col = 1;

    for (std::size_t s = 0; s < _nb_strings - 1; ++s)
    {
        _grid[row][col++] = FRET_BAR;
        _grid[row][col++] = FRET_CROSS;
    }

    _grid[row][width - 2] = FRET_BAR;
    _grid[row][width - 1] = FRET_RIGHT;
}
// exemple avec six cordes et quatre frettes
// ╒═════════╕
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
Grid::Grid(
    std::size_t nb_strings,
    std::size_t nb_frets,
    bool has_nut)
:
_nb_strings(nb_strings),
_nb_frets(nb_frets),
_has_nut(has_nut)
{
    std::size_t width  = 2 * _nb_strings - 1;
    std::size_t height = (_has_nut ? 1 : 0) + 2 * _nb_frets;

    _grid.resize(height);

    for (auto& row : _grid)
        row.resize(width, EMPTY_CELL);

    std::size_t row = 0;

    if (_has_nut)
    {
        add_nut();
        row = 1;
    }

    for (std::size_t f = 0; f < _nb_frets; ++f)
    {
        add_fret(row++);
        add_strings(row++);
    }        
}
void Grid::set_finger(
    STRING string,
    std::size_t case_number,
    DOIGT doigt)
{
    std::size_t s = static_cast<std::size_t>(string);
    std::size_t d = static_cast<std::size_t>(doigt);

    if (s >= _nb_strings) return;
    if (case_number >= _nb_frets) return;

    std::size_t row = (_has_nut ? 1 : 0) + case_number * 2 + 1;
    std::size_t col = s * 2;

    switch (d)
    {
        case 1: _grid[row][col] = "1"; break;
        case 2: _grid[row][col] = "2"; break;
        case 3: _grid[row][col] = "3"; break;
        case 4: _grid[row][col] = "4"; break;
        default: _grid[row][col] = DOT; break;
    }
}
std::string Grid::render()
{
    std::ostringstream oss;

    for (const auto& row : _grid)
    {
        for (const char* c : row)
            oss << c;

        oss << '\n';
    }

    return oss.str();
}
}