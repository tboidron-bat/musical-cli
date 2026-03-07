#pragma once

#include <command_option.h>

namespace cli::chord
{
    class tuning_option : public command::option
    {
    public:
        tuning_option(cli::Command*);

        int execute() const override;
    };

}