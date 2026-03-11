#pragma once

#include <CommandOption.h>

namespace cli::chord
{
    class random_option : public command::Option
    {
    public:
        random_option(cli::Command*);

        int execute() const override;
    };

}