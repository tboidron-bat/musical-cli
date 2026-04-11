#pragma once

#include <Option.h>

namespace cli::chord
{
    class diagram_option : public cli::command::Option
    {
    public:
        diagram_option(cli::Command&);

        int execute() const override;
    };
}