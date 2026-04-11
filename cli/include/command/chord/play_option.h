#pragma once

#include <Option.h>

namespace cli::chord
{
    class play_option : public cli::command::Option
    {
    public:
        play_option(cli::Command&);

        int execute() const override;
    };

}