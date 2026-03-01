#include <chord/diagram_layout.h>

#include <sstream>
#include <algorithm>

namespace cli::chord
{

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

// ------------------------------------------------------------
// Layout principal
// ------------------------------------------------------------
std::string layout_ascii_blocks(
    const std::vector<std::string>& blocks,
    std::size_t max_width,
    std::size_t spacing)
{
    if (blocks.empty())
        return {};

    // 1️⃣ Convertir en matrices de lignes
    std::vector<std::vector<std::string>> matrices;
    matrices.reserve(blocks.size());

    for (const auto& b : blocks)
        matrices.push_back(split_lines(b));

    // 2️⃣ Déterminer dimensions maximales
    std::size_t block_height = 0;
    std::size_t block_width  = 0;

    for (const auto& m : matrices)
    {
        block_height = std::max(block_height, m.size());

        for (const auto& line : m)
            block_width = std::max(block_width, line.size());
    }

    if (block_width == 0)
        return {};

    // 3️⃣ Combien de blocs par ligne ?
    std::size_t per_row =
        std::max<std::size_t>(1,
            max_width / (block_width + spacing));

    std::ostringstream out;

    // 4️⃣ Impression par groupes
    for (std::size_t i = 0; i < matrices.size(); i += per_row)
    {
        std::size_t end = std::min(i + per_row, matrices.size());

        for (std::size_t row = 0; row < block_height; ++row)
        {
            for (std::size_t col = i; col < end; ++col)
            {
                if (row < matrices[col].size())
                {
                    const auto& line = matrices[col][row];
                    out << line;

                    if (line.size() < block_width)
                        out << std::string(block_width - line.size(), ' ');
                }
                else
                {
                    out << std::string(block_width, ' ');
                }      
                if (col + 1 < end)
                    out << std::string(spacing, ' ');      }
            out << '\n';
        }

        out << '\n';
    }

    return out.str();
}

} // namespace cli::chord