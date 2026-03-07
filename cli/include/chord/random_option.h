#pragma once

#include <command_option.h>

namespace cli::chord
{
    class random_option : public command::option
    {
    public:
        random_option(cli::Command*);

        int execute() const override;
    };

}