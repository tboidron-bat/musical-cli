#include <command/chord/diagram_layout.h>

#include <sstream>
#include <algorithm>

#include <wchar.h>
#include <locale>

static std::size_t visual_width(const std::string& s)
{
    std::mbstate_t state{};
    const char* ptr = s.c_str();
    wchar_t wc;

    std::size_t width = 0;

    while (*ptr)
    {
        std::size_t len =
            std::mbrtowc(&wc, ptr, MB_CUR_MAX, &state);

        if (len == (std::size_t)-1 || len == (std::size_t)-2)
            break;

        int w = wcwidth(wc);

        if (w > 0)
            width += w;

        ptr += len;
    }

    return width;
}

namespace cli::chord
{

Layout::Layout(
    std::size_t terminal_width,
    int h_space_between_blocks,
    int v_space_between_blocks)
:
_terminal_width(terminal_width),
_h_space_between_blocks(h_space_between_blocks),
_v_space_between_blocks(v_space_between_blocks)
{
}

void Layout::add_block(const std::string& block)
{
    std::stringstream ss(block);
    std::string line;

    std::vector<std::string> lines;

    while (std::getline(ss, line))
        lines.push_back(line);

    _blocks.push_back(std::move(lines));
}

std::size_t Layout::compute_block_width() const
{
    std::size_t width = 0;

    for (const auto& block : _blocks)
    {
        for (const auto& line : block)
            width = std::max(width, visual_width(line));
    }

    return width;
}

std::size_t Layout::compute_blocks_per_line() const
{
    std::size_t block_width = compute_block_width();

    std::size_t total_block_width =
        block_width + _h_space_between_blocks;

    if (total_block_width == 0)
        return 1;

    std::size_t cols =
        _terminal_width / total_block_width;

    return std::max<std::size_t>(1, cols);
}

std::string Layout::render() const
{
    if (_blocks.empty())
        return "";

    std::size_t block_width = compute_block_width();
    std::size_t cols = compute_blocks_per_line();

    std::ostringstream out;

    for (std::size_t i = 0; i < _blocks.size(); i += cols)
    {
        std::size_t end =
            std::min(i + cols, _blocks.size());

        std::size_t local_height = 0;

        for (std::size_t b = i; b < end; ++b)
            local_height = std::max(local_height, _blocks[b].size());

        for (std::size_t row = 0; row < local_height; ++row)
        {
            for (std::size_t b = i; b < end; ++b)
            {
                const auto& block = _blocks[b];

                if (row < block.size())
                    out << block[row];
                else
                    out << std::string(block_width, ' ');

                if (b + 1 < end)
                    out << std::string(_h_space_between_blocks, ' ');
            }

            out << '\n';
        }

        out << std::string(_v_space_between_blocks, '\n');
    }

    return out.str();
}

}