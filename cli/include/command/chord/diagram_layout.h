#pragma once

#include <string>
#include <vector>
#include <cstddef>

#include <terminal.h>

namespace cli::chord
{
class Layout
{
private:
    std::vector<std::vector<std::string>> _blocks;

    int _h_space_between_blocks;
    int _v_space_between_blocks;

    std::size_t _terminal_width;

public:

    Layout(
        std::size_t terminal_width,
        int h_space_between_blocks = 3,
        int v_space_between_blocks = 1);

    void add_block(const std::string& block);

    std::string render() const;

private:
    std::size_t compute_block_width() const;
    std::size_t compute_blocks_per_line() const;
};
}