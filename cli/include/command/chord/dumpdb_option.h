#pragma once

#include <CommandOption.h>

namespace cli::chord
{
    class dumpdb_option : public command::Option
    {
    public:
        dumpdb_option(cli::Command*);

        int execute() const override;
    };

}