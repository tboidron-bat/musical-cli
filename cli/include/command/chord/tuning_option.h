#pragma once

#include <CommandOption.h>

namespace cli::chord
{
    class tuning_option : public command::Option
    {
    public:
        tuning_option(cli::Command*);

        int execute() const override;
    };

}