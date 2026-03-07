#include <chord/tuning_option.h>

namespace cli::chord
{
    tuning_option::tuning_option(cli::Command*cmd)
    :
    cli::command::option(cmd,"tuning","","Guitar tuning to use for diagram rendering")
    {

        add_parameter({
            cli::command::option::parameter_t::Type::STRING,
            "",
            "standard, dropd"
            });

        // "Supported tunings:\n"
        // "standard   (E A D G B E)\n"
        // "dropd      (D A D G B E)\n"
        // "Default: standard.\n"

    }
    int tuning_option::execute() const
    {
    }
}


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
