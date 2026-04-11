#pragma once

#include <Option.h>

namespace cli::chord
{
    class version_option : public cli::command::Option
    {
    public:
        version_option(cli::Command&);

        int execute() const override;
    };

}