#include <musical/io/guitar/unicode/DottedGrid.h>

#include <sstream>

namespace io::guitar::unicode
{
//      .
//      .
//      .
void DottedGrid::add_dots()
{
    GridCore::row_t dot_row(_grid.width(), EMPTY_CELL);

    std::size_t center = _grid.width() / 2;
    dot_row[center] = ".";

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
void DottedGrid::enlarge()
{
    for (std::size_t r = 0; r < _grid.height(); ++r)
    {
        auto& row = _grid.row(r);

        row.resize(
            row.size() + DEFAULT_RIGHT_SPACING,
            EMPTY_CELL
        );
    }
}
void DottedGrid::set_case_annotation(
    std::size_t case_number,
    const std::string& txt)
{
    // position de la ligne correspondant à la case
    std::size_t r = 2 + case_number * 2;

    if (r >= _grid.height())
        return;

    GridCore::row_t& row = _grid.row(r);

    std::size_t start = row.size() - DEFAULT_RIGHT_SPACING;

    for (std::size_t i = 0; i < txt.size() && start + i < row.size(); ++i)
    {
        static std::vector<std::string> storage;
        storage.emplace_back(1, txt[i]);
        row[start + i] = storage.back().c_str();
    }
}
}
