#include <musical/io/chord_db/unicode/GridCore.h>

#include <sstream>

namespace io::chord::db::unicode
{

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
    : _nb_strings(nb_strings)
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
        default:                 _grid[r][c] = BIG_DOT;
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

    _grid[r][c] = BIG_DOT;
}


void GridCore::extend_right()
{
    if (_extended_right)
        return;

    for (auto& r : _grid)
    {
        r.resize(r.size() + RIGHT_SPACING, EMPTY_CELL);
    }

    _extended_right = true;    
}


void GridCore::write_right(std::size_t row, const std::string& txt)
{
    extend_right(); // toujours safe
    
    if (row >= _grid.size())
        return;

    auto& r = _grid[row];

    if (r.size() < RIGHT_SPACING)
        return;

    std::size_t start = r.size() - RIGHT_SPACING + 1;

    for (std::size_t i = 0;
         i < txt.size() && i < RIGHT_SPACING;
         ++i)
    {
        r[start + i] = std::string(1, txt[i]);
    }
}
void GridCore::add_title_row(const std::string& text)
{
    std::size_t total_w = width();

    std::size_t usable_w =
        _extended_right ? total_w - RIGHT_SPACING
                        : total_w;

    row_t row(total_w, " ");

    std::size_t start =
        (text.size() < usable_w)
        ? (usable_w - text.size()) / 2
        : 0;

    for (std::size_t i = 0;
         i < text.size() && (start + i) < usable_w;
         ++i)
    {
        row[start + i] = std::string(1, text[i]);
    }
    insert_row_top(std::move(row));
}
void GridCore::write_caged_row(const std::string& caged_text)
{
    std::size_t total_w = width();

    std::size_t usable_w =
        _extended_right ? total_w - RIGHT_SPACING
                        : total_w;       
                        
    row_t row(total_w, " ");
    
    std::size_t start =
        (caged_text.size() < usable_w)
        ? (usable_w - caged_text.size()) / 2
        : 0;    

    for (std::size_t i = 0;
         i < caged_text.size() && (start + i) < usable_w;
         ++i)
    {
        row[start + i] = std::string(1, caged_text[i]);
    }

    insert_row_top(std::move(row));        
}
std::string GridCore::render() const
{
    std::ostringstream oss;

    for (const auto& row : _grid)
    {
        for (const std::string& cell : row)
            oss << cell;

        oss << '\n';
    }

    return oss.str();
}
//HACK: pour ajouter des lignes vides en haut.
void GridCore::pad_top(std::size_t n)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        row_t row(width(), EMPTY_CELL);
        insert_row_top(std::move(row));
    }
}

} // namespace