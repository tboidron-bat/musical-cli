#include <command_option.h>
#include <stdexcept>

namespace cli::command
{
bool option::parse(int argc, char** argv)
{
    for(int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        bool match = false;

        if(arg == "--" + _name)
            match = true;

        if(!_short_name.empty() && arg == "-" + _short_name)
            match = true;

        if(!match)
            continue;

        // option trouvée

        if(_arguments.empty())
            return true;

        // lire les valeurs attendues
        for(std::size_t k = 0; k < _arguments.size(); ++k)
        {
            if(i + 1 >= argc)
                throw std::runtime_error(
                    "Missing value for option --" + _name
                );

            _arguments[k]._value = argv[++i];
        }

        return true;
    }

    return false;
}
std::string option::print_usage() const
{
    std::string result;

    result += "--" + _name;

    if(!_short_name.empty())
        result += " (-" + _short_name + ")";

    for(const auto& arg : _arguments)
        result += " <" + arg._name + ">";

    result += "\n";
    result += "  " + _description + "\n";

    for(const auto& arg : _arguments)
        result += "    " + arg._description + "\n";

    return result;
}
} //namespace cli::command 

// const std::vector<cli::option_t>&
// ChordCommand::options() const
// {
//     static const std::vector<cli::option_t> opts =
//     {
        // {
        //     "--diagram",
        //     "-d",
        //     "Show chord diagram.\n"
        //     "If <value> (1–5) is provided, show only that CAGED position.",
        //     true,
        //     true,
        //     1,
        //     std::vector<std::string>{ "1","2","3","4","5" }
        // },
        // {
        //     "--random",
        //     "-r",
        //     "Show a completely random chord.",
        //     false,
        //     false,
        //     0,
        //     {}
        // },
        // {
        //     "--play",
        //     "",
        //     "Play the chord using Karplus-Strong guitar synthesis.\n"
        //     "Usage:\n"
        //     "  --play                 (simultaneous attack)\n"
        //     "  --play <delay_ms>\n"
        //     "  --play <delay_ms> <downstroke>\n"
        //     "\n"
        //     "Examples:\n"
        //     "  --play\n"
        //     "  --play 15\n"
        //     "  --play 20 false\n",
        //     true,   // accepte des valeurs (0 à 2)
        //     true,   // valeurs optionnelles
        //     2,
        //     {}
        // },
        // {
        //     "--difficulty",
        //     "",
        //     "Filter diagrams by difficulty level (1–3).\n"
        //     "Requires --diagram.",
        //     true,
        //     false,
        //     1,
        //     std::vector<std::string>{ "1","2","3" }
        // },
        // {
        //     "--dump-db",
        //     "",
        //     "Dump all chord diagrams stored in the database.",
        //     false,
        //     false,
        //     0,
        //     {}
        // },        
        // {
        //     "--tuning",
        //     "",
        //     "Guitar tuning to use for diagram rendering.\n"
        //     "Supported tunings:\n"
        //     "standard   (E A D G B E)\n"
        //     "dropd      (D A D G B E)\n"
        //     "Default: standard.\n"
        //     "Requires --diagram.",
        //     true,
        //     false,
        //     1,
        //     std::vector<std::string>{ "standard","dropd" }
        // }
    //};

    //return opts;
//}    





