#pragma once

#include <command_option.h>

namespace cli::chord
{
    class dumpdb_option : public command::option
    {
    public:
        dumpdb_option(cli::Command*);

        int execute() const override;
    };

}