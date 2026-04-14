#pragma once

#include <Option.h>

namespace cli::command::chord
{
    class diagram : public cli::command::Option
    {
    public:
        diagram(cli::Command&);

        int execute() const override;
    };
}