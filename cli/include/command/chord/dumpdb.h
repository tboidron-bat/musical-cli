#pragma once

#include <Option.h>
#include <command/chord/ChordCommand.h>

namespace cli::command::chord
{
    class dumpdb : public cli::command::Option
    {
    public:
        dumpdb(cli::Command&);

        int execute() const override;
    private:

        void add_all_diagrams(cli::chord::ChordCommand&) const;        
    };

}