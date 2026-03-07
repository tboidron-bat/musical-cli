#pragma once

#include <command_option.h>

namespace cli::chord
{
    class play_option : public command::option
    {
    public:
        play_option(cli::Command*);

        int execute() const override;
    };

}