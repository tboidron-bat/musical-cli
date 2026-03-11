#pragma once

#include <CommandOption.h>

namespace cli::chord
{
    class diagram_option : public command::Option
    {
    public:
        diagram_option(cli::Command*);

        int execute() const override;
    };

}