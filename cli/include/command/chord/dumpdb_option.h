#pragma once

#include <Option.h>

namespace cli::chord
{
    class dumpdb_option : public command::Option
    {
    public:
        dumpdb_option(cli::Command&);

        int execute() const override;
    private:
        int dump_open_diagrams(int width) const;
        int dump_movable_diagrams(int width) const;
    };

}