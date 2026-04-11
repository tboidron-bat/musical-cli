#include <command/chord/diagram_option.h>
#include <command/chord/ChordCommand.h>

#include <algorithm>

#include <optional>
#include <string>
#include <iostream>

namespace cli::chord
{

diagram_option::diagram_option(cli::Command& cmd)
:
cli::command::Option(
    cmd,
    "diagram",
    "d",
    "Show all known guitar chord diagram for the given chord")
{
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "value",
        "If <value> (1–5) is provided, show only that CAGED position",
        command::option::parameter_t::Requirement::OPTIONAL,
        { "1","2","3","4","5" }
    });

    //TODO
    // add_parameter({
    //     cli::command::option::parameter_t::Type::STRING,
    //     "source",
    //     "Limit diagrams to a specific source (open, movable)",
    //     command::option::parameter_t::Requirement::OPTIONAL,
    //     { "open", "movable" }
    // });    
}
// ============================================================
// EXECUTE
// ============================================================
int diagram_option::execute() const 
{
    if(!_enabled)
        return EXIT_FAILURE;

    auto& cmd = static_cast<ChordCommand&>(_command_ref);        

    auto& entries = cmd.entries();

    std::optional<::chord::db::Diagram::CAGED> caged;

    if(parameter(0)._provided)
    {
        int v = -1;
        try{
            v = std::stoi(parameter(0)._value);
            if(v < 1 || v > 5)
            {
                std::cerr << "Invalid CAGED position: " << v << "\n";
                return EXIT_FAILURE;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Invalid parameter for --diagram option: " << parameter(0)._value << "\n";
            return EXIT_FAILURE;
        }
        caged = static_cast<::chord::db::Diagram::CAGED>(v - 1);
    }


    if(caged)
    {
        entries.erase(
            std::remove_if(
                entries.begin(),
                entries.end(),
                [&](const auto& e)
                {
                    return e._diagram.caged() != *caged;
                }),
            entries.end()
        );
    }

    return EXIT_SUCCESS;
}

} // namespace cli::chord


