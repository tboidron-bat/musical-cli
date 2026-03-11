#include <chord/Usage.h>
#include <command/chord/ChordCommand.h>

#include <iostream>
#include <sstream>

namespace cli::chord
{
// ------------------------------------------------------------
// Help
// ------------------------------------------------------------
void print_help(const ChordCommand& cmd)
{
    std::cout << "Chord CLI — version 0.01\n\n";

    std::cout <<
        "Usage:\n"
        "  chord [options] <symbol>\n";

    std::cout << "\nOptions:\n\n";

    const auto& options = cmd.options();

    // ------------------------------------------------------------
    // 1️⃣ Construire les labels d’options
    // ------------------------------------------------------------
    std::vector<std::string> labels;
    labels.reserve(options.size());

    std::size_t max_width = 0;

    for (const auto& opt : options)
    {
        std::ostringstream label;

        if (!opt._short_name.empty())
            label << opt._short_name << ", ";

        label << opt._long_name;

        if (opt.takes_value)
        {
            if (opt.value_optional)
                label << " [value]";
            else
                label << " <value>";
        }

        labels.push_back(label.str());
        max_width = std::max(max_width, labels.back().size());
    }

    const std::size_t left_padding = 2;
    const std::size_t description_indent = left_padding + max_width + 4;

    // ------------------------------------------------------------
    // 2️⃣ Affichage aligné
    // ------------------------------------------------------------
    for (std::size_t i = 0; i < options.size(); ++i)
    {
        const auto& opt = options[i];
        const auto& label = labels[i];

        // Affiche label aligné
        std::cout << std::string(left_padding, ' ')
                  << label
                  << std::string(max_width - label.size() + 4, ' ');

        // Description multi-ligne
        std::istringstream iss(opt._description);
        std::string line;
        bool first_line = true;
        bool in_sub_block = false;

        while (std::getline(iss, line))
        {
            if (!first_line)
                std::cout << std::string(description_indent, ' ');

            // gestion des sous-blocs
            if (!line.empty() && line.back() == ':')
            {
                std::cout << line << "\n";
                in_sub_block = true;
            }
            else if (in_sub_block)
            {
                if (line.find(':') != std::string::npos)
                {
                    in_sub_block = false;
                    std::cout << line << "\n";
                }
                else
                {
                    std::cout << "    " << line << "\n";
                }
            }
            else
            {
                std::cout << line << "\n";
            }

            first_line = false;
        }

        std::cout << "\n";
    }
}
} // namespace cli::chord