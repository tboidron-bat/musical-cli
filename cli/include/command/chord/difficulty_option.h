#pragma once

#include <CommandOption.h>

namespace cli::chord
{
    class difficulty_option : public command::Option
    {
    public:
        difficulty_option(cli::Command*);

        int execute() const override;
    };

}