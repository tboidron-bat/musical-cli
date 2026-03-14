#include <command/chord/tuning_option.h>

namespace cli::chord
{
tuning_option::tuning_option(cli::Command&cmd)
:
cli::command::Option(cmd,"tuning","","Guitar tuning to use for diagram rendering")
{
    add_parameter({
        cli::command::option::parameter_t::Type::STRING,
        "",
        "standard, dropd",
        command::option::parameter_t::Requirement::REQUIRED
        });

    //  "Supported tunings:\n"
    //  "standard   (E A D G B E)\n"
    //  "dropd      (D A D G B E)\n"
    //  "Default: standard.\n"
    //  "Requires --diagram.",
    //  std::vector<std::string>{ "standard","dropd" }

}
int tuning_option::execute() const
{
    return 0;
}
}


