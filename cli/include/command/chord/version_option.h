#pragma once

#include <CommandOption.h>

namespace cli::chord
{
    class version_option : public command::Option
    {
    public:
        version_option(cli::Command*);

        int execute() const override;
    };

}