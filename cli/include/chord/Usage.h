#pragma once

namespace cli::chord
{
    class ChordCommand;   // forward declaration

    void print_usage();
    void print_help(const ChordCommand&);
}