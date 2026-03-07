#pragma once

#include <command_option.h>

namespace cli::chord
{
    class diagram_option : public command::option
    {
    public:
        diagram_option(cli::Command*);

        int execute() const override;
    };

}