#pragma once

#include <vector>
#include <command/chord/ChordCommand.h>

namespace cli::command::chord
{
    /**
     * Render chord diagrams (open + movable) to stdout.
     */
    void render_diagrams(
        const std::vector<cli::chord::ChordCommand::diagram_entry_t>& entries
    );
}