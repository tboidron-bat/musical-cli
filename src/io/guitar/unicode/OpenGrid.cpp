#include <musical/io/guitar/unicode/OpenGrid.h>

#include <sstream>
//#include <iostream> //DEBUG

namespace io::guitar::unicode
{
// x x 0  0
//    
void OpenGrid::add_open_strings_row()
{
    GridCore::row_t row(_grid.width(), EMPTY_CELL);

    for (std::size_t col = 0; col < _grid.width(); col += 2)
        row[col] = " ";

    _grid.insert_row_top(std::move(row));
}
// ╒═════════╕
//    
void OpenGrid::add_nut_row()
{
    GridCore::row_t row(_grid.width(), EMPTY_CELL);

    row[0] = NUT_LEFT;

    for (std::size_t i = 1; i < _grid.width() - 1; ++i)
        row[i] = NUT_BAR;

    row[_grid.width() - 1] = NUT_RIGHT;

    _grid.insert_row_top(std::move(row));
}
OpenGrid::OpenGrid(std::size_t nb_strings,
                   std::size_t nb_cases)
    : _grid(nb_strings, nb_cases)
{
    add_nut_row();
    add_open_strings_row();
}
void OpenGrid::set_finger(
    GridCore::STRING string,
    std::size_t case_number,
    GridCore::DOIGT doigt)
{
    _grid.set_finger(string, case_number + 1, doigt);
}
void OpenGrid::set_finger(
    GridCore::STRING string,
    std::size_t case_number)
{
    _grid.set_finger(string, case_number + 1);
}
void OpenGrid::set_open_string(GridCore::STRING string)
{
    std::size_t col = static_cast<std::size_t>(string) * 2;
    _grid.row(0)[col] = OPEN_CHAR;   
}
void OpenGrid::set_muted_string(GridCore::STRING string)
{
    std::size_t col = static_cast<std::size_t>(string) * 2;
    _grid.row(0)[col] = MUTED_CHAR;
}
std::string OpenGrid::render() const
{
    return _grid.render();
}
}