#pragma once

#include <CommandOption.h>

namespace cli::chord
{
class help_option : public cli::command::Option
{
public:

    help_option(cli::Command* cmd)
    :
    Option(
        cmd,
        "help",
        "h",
        "Show help message")
    {}

    int execute() const override;

};

}