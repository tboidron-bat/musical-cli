#pragma once

#include <command_option.h>

namespace cli::chord
{
    class difficulty_option : public command::option
    {
    public:
        difficulty_option(cli::Command*);

        int execute() const override;
    };

}