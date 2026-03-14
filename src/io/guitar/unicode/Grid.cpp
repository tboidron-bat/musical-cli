#include <musical/io/guitar/unicode/Grid.h>

#include <sstream>

namespace io::guitar::unicode
{
//
// x x 0  0
//    
void Grid::add_open_strings_row()
{
    std::vector<const char*> row(width(), EMPTY_CELL);

    std::size_t col = 0;

    for (std::size_t s = 0; s < _nb_strings; ++s)
    {
        row[col] = " ";   // par défaut
        col += 2;
    }

    _grid.push_back(row);
}
//
// ╒═════════╕
//    
void Grid::add_nut_row()
{
    std::vector<const char*> row(width(), EMPTY_CELL);

    row[0] = NUT_LEFT;

    for (std::size_t i = 1; i < width() - 1; ++i)
        row[i] = NUT_BAR;

    row[width() - 1] = NUT_RIGHT;

    _grid.push_back(row);
}
//
//│ │ │ │ │ │
//
void Grid::add_strings_row()
{
    std::vector<const char*> row(width(), EMPTY_CELL);

    std::size_t col = 0;

    for (std::size_t s = 0; s < _nb_strings; ++s)
    {
        row[col] = STRING_CHAR;
        col += 2;
    }

    _grid.push_back(row);
}
//
//├─┼─┼─┼─┼─┤
//
void Grid::add_fret_row()
{
    std::vector<const char*> row(width(), EMPTY_CELL);

    row[0] = FRET_LEFT;

    std::size_t col = 1;

    for (std::size_t s = 0; s < _nb_strings - 1; ++s)
    {
        row[col++] = FRET_BAR;
        row[col++] = FRET_CROSS;
    }

    row[width() - 2] = FRET_BAR;
    row[width() - 1] = FRET_RIGHT;

    _grid.push_back(row);
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
    std::size_t nb_case,
    bool has_nut)
:
_nb_strings(nb_strings),
_has_nut(has_nut)
{
    if (_has_nut)
    {
        add_open_strings_row();
        add_nut_row();
    }

    for (std::size_t f = 0; f < nb_case; ++f)
    {
        add_fret_row();
        add_strings_row();
    }        
}
void Grid::set_finger(
    STRING string,
    std::size_t case_number,
    DOIGT doigt)
{
    std::size_t row = (_has_nut ? 2 : 0) + case_number * 2 + 1;
    std::size_t col = static_cast<std::size_t>(string) * 2;

    if (row >= _grid.size())
        return;    
    if (col >= width())
        return;


    switch (doigt)
    {
        case DOIGT::INDEX:      _grid[row][col] = "1"; break;
        case DOIGT::MAJEUR:     _grid[row][col] = "2"; break;
        case DOIGT::ANNULAIRE:  _grid[row][col] = "3"; break;
        case DOIGT::AURICULAIRE:_grid[row][col] = "4"; break;
        default:                _grid[row][col] = DOT;
    }
}
void Grid::set_open_string(STRING string)
{
    if(!_has_nut) return;

    std::size_t s = static_cast<std::size_t>(string);
    std::size_t col = s * 2;

    _grid[0][col] = OPEN_CHAR;
}
void Grid::set_muted_string(STRING string)
{
   if(!_has_nut) return;

    std::size_t s = static_cast<std::size_t>(string);
    std::size_t col = s * 2;

    _grid[0][col] = MUTED_CHAR;
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