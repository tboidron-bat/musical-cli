#include <ArgumentParser.h>
#include <stdexcept>

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
        // Flags globaux simples
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
        // Options avec valeur possible
        // ----------------------------
        if (!arg.empty() && arg[0] == '-')
        {
            std::optional<std::string> value;

            // regarde si prochain argument existe
            if (i + 1 < argc)
            {
                std::string next = argv[i + 1];

                // si le prochain n'est pas une option,
                // on le considère comme valeur
                if (!next.empty() && next[0] != '-')
                {
                    value = next;
                    ++i; // on consomme la valeur
                }
            }

            cfg.options[arg] = value;
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