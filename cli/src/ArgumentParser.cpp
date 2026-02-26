#include <ArgumentParser.h>
#include <stdexcept>
#include <cctype>

namespace cli
{

globalconfig_t 
ArgumentParser::parse(int argc, char** argv)
{
    globalconfig_t cfg;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        // ----------------------------
        // Flags globaux
        // ----------------------------
        if (arg == "-h" || arg == "--help")
        {
            cfg.help = true;
            continue;
        }

        if (arg == "-v" || arg == "--version")
        {
            cfg.version = true;
            continue;
        }

        if (arg == "--verbose")
        {
            cfg.verbose = true;
            continue;
        }

        if (arg == "--json")
        {
            cfg.json = true;
            continue;
        }

        // ----------------------------
        // Options multi-valeurs
        // ----------------------------
        if (!arg.empty() && arg[0] == '-')
        {
            std::vector<std::string> values;

            // Lire tous les arguments suivants
            // jusqu'à tomber sur une nouvelle option
            while (i + 1 < argc)
            {
                std::string next = argv[i + 1];

                bool next_is_option =
                    next.size() > 1 && next[0] == '-' && next[1] == '-';

                bool next_is_negative_number =
                    next.size() > 1 && next[0] == '-' && std::isdigit(next[1]);

                if (next_is_option && !next_is_negative_number)
                    break;

                values.push_back(next);
                ++i;
            }

            cfg.options[arg] = values;
            continue;
        }

        // ----------------------------
        // Positionnels
        // ----------------------------
        cfg.positional_args.push_back(arg);
    }

    return cfg;
}

} // namespace cli