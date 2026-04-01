#include <musical/io/guitar/unicode/DottedGrid.h>

namespace io::guitar::unicode
{
//      •
//      •
//      •
void DottedGrid::add_dots()
{
    GridCore::row_t dot_row(_grid.width(), EMPTY_CELL);

    std::size_t center = _grid.width() / 2;
    dot_row[center] = "•";

    // inséré après le nut
    // inséré après le nut (ligne 2)
    constexpr std::size_t INSERT_INDEX = 2;    

    for (std::size_t i = 0; i < 3; ++i)
        _grid.insert_row(INSERT_INDEX, dot_row);
}
DottedGrid::DottedGrid(std::size_t nb_strings,
                       std::size_t nb_cases)
: 
OpenGrid(nb_strings, nb_cases)
{
    add_dots();
}
}
