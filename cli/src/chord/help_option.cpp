#include <chord/help_option.h>
#include <chord/ChordCommand.h>

#include <iostream>

namespace cli::chord
{

int help_option::execute() const
{
    auto* cmd = static_cast<ChordCommand*>(_command);

    cmd->print_help();

    return 0;
}
}