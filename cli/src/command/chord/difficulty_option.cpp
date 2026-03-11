#include <command/chord/difficulty_option.h>

namespace cli::chord
{
difficulty_option::difficulty_option(cli::Command*cmd)
:   
command::Option(cmd,
    "difficulty",
    "",
    "Filter diagrams by difficulty level (1–3)")
{
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "level",
        "1, 2, 3",
        command::option::parameter_t::Requirement::REQUIRED
        });

        //TODO Requires --diagram.
}
int difficulty_option::execute() const
{
    return 0;
}
}

        //     "--difficulty",
        //     "",
        //     "Filter diagrams by difficulty level (1–3).\n"
        //     "Requires --diagram.",
        //     true,
        //     false,
        //     1,
        //     std::vector<std::string>{ "1","2","3" }
