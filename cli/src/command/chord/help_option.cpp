#include <command/chord/help_option.h>
#include <command/chord/ChordCommand.h>

#include <iostream>

namespace cli::chord
{

int help_option::execute() const
{
    if(!_enabled)
        return 0;

    auto& cmd = static_cast<ChordCommand&>(_command_ref);

    cmd.print_help();

    return 1;
}
}