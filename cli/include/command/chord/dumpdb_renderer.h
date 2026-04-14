#pragma once

#include <vector>
#include <command/chord/ChordCommand.h>

namespace cli::command::chord
{
    void render_dumpdb(const std::vector<cli::chord::ChordCommand::diagram_entry_t>& entries);
}