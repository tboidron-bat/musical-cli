#include <command/chord/diagram_layout.h>

#include <sstream>
#include <algorithm>


#include <wchar.h>
#include <locale>

static size_t utf8_width(const std::string& s)
{
    std::mbstate_t state{};
    const char* ptr = s.data();
    size_t len = s.size();

    wchar_t wc;
    size_t width = 0;

    while(len > 0)
    {
        size_t r = mbrtowc(&wc, ptr, len, &state);

        if(r == (size_t)-1 || r == (size_t)-2)
            break;

        int w = wcwidth(wc);
        if(w > 0)
            width += w;

        ptr += r;
        len -= r;
    }

    return width;
}

// ------------------------------------------------------------
// Utilitaire : split multi-lignes
// ------------------------------------------------------------
std::vector<std::string>
split_lines(const std::string& block)
{
    std::vector<std::string> lines;
    std::istringstream iss(block);
    std::string line;

    while (std::getline(iss, line))
        lines.push_back(line);

    return lines;
}

std::string layout_blocks(
    const std::vector<std::string>& blocks,
    std::size_t term_width,
    std::size_t spacing)
{
    if(blocks.empty())
        return {};

    std::vector<std::vector<std::string>> matrices;

    for(const auto& b : blocks)
        matrices.push_back(split_lines(b));

    size_t block_height = 0;
    size_t block_width  = 0;

    for(const auto& m : matrices)
    {
        block_height = std::max(block_height, m.size());

        for(const auto& line : m)
            block_width = std::max(block_width, utf8_width(line));
    }

    size_t col_width = block_width + spacing;

    size_t per_row = std::max<size_t>(1, term_width / col_width);

    std::ostringstream out;

    for(size_t i = 0; i < matrices.size(); i += per_row)
    {
        size_t end = std::min(i + per_row, matrices.size());

        for(size_t row = 0; row < block_height; ++row)
        {
            for(size_t col = i; col < end; ++col)
            {
                if(row < matrices[col].size())
                {
                    const auto& line = matrices[col][row];

                    size_t w = utf8_width(line);

                    out << line;

                    if(w < block_width)
                        out << std::string(block_width - w, ' ');
                }
                else
                {
                    out << std::string(block_width, ' ');
                }

                if(col + 1 < end)
                    out << std::string(spacing, ' ');
            }

            out << '\n';
        }

        out << '\n';
    }

    return out.str();
}