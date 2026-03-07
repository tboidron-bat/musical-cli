#include <chord/difficulty_option.h>

namespace cli::chord
{
difficulty_option::difficulty_option(cli::Command*cmd)
:   
cli::command::option(cmd,
    "difficulty",
    "",
    "Filter diagrams by difficulty level (1–3)")
{
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "level",
        "1, 2, 3"
        });
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
