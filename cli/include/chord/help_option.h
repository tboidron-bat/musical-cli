#pragma once

#include <command_option.h>

namespace cli::chord
{
class help_option : public cli::command::option
{
public:

    help_option(cli::Command* cmd)
        :
        option(
            cmd,
            "help",
            "h",
            "Show help message")
    {}

    int execute() const override;
};

}