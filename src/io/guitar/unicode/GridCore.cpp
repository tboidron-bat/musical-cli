#include <musical/io/guitar/unicode/GridCore.h>

#include <sstream>
#include <cstring>

namespace io::guitar::unicode
{

static constexpr std::size_t RIGHT_SPACING = 4;    

// │ │ │ │ │ │
void GridCore::add_strings_row()
{
    const std::size_t w = 2 * _nb_strings - 1;

    row_t row(w, EMPTY_CELL);

    std::size_t col = 0;

    for (std::size_t s = 0; s < _nb_strings; ++s)
    {
        row[col] = STRING_CHAR;
        col += 2;
    }

    push_row(std::move(row));
}


// ├─┼─┼─┼─┼─┤
void GridCore::add_fret_row()
{
    const std::size_t w = 2 * _nb_strings - 1;

    row_t row(w, EMPTY_CELL);

    row[0] = FRET_LEFT;

    std::size_t col = 1;

    for (std::size_t s = 0; s < _nb_strings - 1; ++s)
    {
        row[col++] = FRET_BAR;
        row[col++] = FRET_CROSS;
    }

    row[w - 2] = FRET_BAR;
    row[w - 1] = FRET_RIGHT;

    push_row(std::move(row));
}
// ├─┼─┼─┼─┼─┤
// │ │ │ │ │ │
void GridCore::add_case_row()
{
    add_fret_row();
    add_strings_row();
}
GridCore::GridCore(
    const std::size_t nb_strings,
    const std::size_t nb_cases)
:
_nb_strings(nb_strings)
{
    for (std::size_t f = 0; f < nb_cases; ++f)
    {
        add_case_row();
    }
}
void GridCore::set_finger(
    STRING string,
    std::size_t case_number,
    DOIGT doigt)
{
    const std::size_t r = case_number * 2 + 1;
    const std::size_t c = static_cast<std::size_t>(string) * 2;

    if (r >= _grid.size() || c >= width())
        return;

    switch (doigt)
    {
        case DOIGT::INDEX:       _grid[r][c] = "1"; break;
        case DOIGT::MAJEUR:      _grid[r][c] = "2"; break;
        case DOIGT::ANNULAIRE:   _grid[r][c] = "3"; break;
        case DOIGT::AURICULAIRE: _grid[r][c] = "4"; break;
        default:                 _grid[r][c] = DOT;
    }
}
void GridCore::set_finger(
    STRING string,
    std::size_t case_number)
{
    const std::size_t r = case_number * 2 + 1;
    const std::size_t c = static_cast<std::size_t>(string) * 2;

    if (r >= _grid.size() || c >= width())
        return;

    _grid[r][c] = "●"; // ou DOT si déjà défini
}
void GridCore::extend_right()
{
    for (auto& r : _grid)
    {
        r.resize(r.size() + RIGHT_SPACING, EMPTY_CELL);
    }
}
void GridCore::write_right(std::size_t row, const std::string& txt)
{
    if (row >= _grid.size())
        return;

    auto& r = _grid[row];

    if (r.size() < RIGHT_SPACING)
        return;

    std::size_t start = r.size() - RIGHT_SPACING + 1;

    for (std::size_t i = 0; i < txt.size() && i < RIGHT_SPACING; ++i)
    {
        r[start + i] = strdup(std::string(1, txt[i]).c_str());    
    }
}
std::string GridCore::render() const
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
