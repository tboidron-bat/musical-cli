#include <musical/io/chord_db/unicode/OpenGrid.h>

//#include <iostream> //DEBUG

namespace io::chord::db::unicode
{
// x x 0  0
//    
void OpenGrid::add_open_strings_row()
{
    GridCore::row_t row(_grid.width(), EMPTY_CELL);
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
    Finger finger)
{
    _grid.set_finger(string, case_number + 1, finger);
}
// o 
void OpenGrid::set_open_string(GridCore::STRING string)
{
    std::size_t col = static_cast<std::size_t>(string) * 2;
    _grid.row(0)[col] = OPEN_CHAR;   
}
// x 
void OpenGrid::set_muted_string(GridCore::STRING string)
{
    std::size_t col = static_cast<std::size_t>(string) * 2;
    _grid.row(0)[col] = MUTED_CHAR;
}
std::size_t OpenGrid::height() const
{
    return _grid.height() + 2;
}
std::size_t OpenGrid::width() const
{
    return _grid.width();
}    
std::string OpenGrid::render() const
{
    return _grid.render();
}
void OpenGrid::write_right(std::size_t row, const std::string& txt)
{
    _grid.write_right(row, txt);
}
}