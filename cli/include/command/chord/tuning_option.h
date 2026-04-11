#pragma once

#include <Option.h>

namespace cli::chord
{
    class tuning_option : public cli::command::Option
    {
    public:
        tuning_option(cli::Command&);

        int execute() const override;
    };

}