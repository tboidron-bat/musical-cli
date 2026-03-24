#pragma once

#include <vector>
#include <string>
#include <utility>

#include <musical/Core/pitch_t.h>
#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database::queries::open
{

// ------------------------------------------------------------
// FIND POSITIONS (pitch + chord_name)
// ------------------------------------------------------------
std::vector<Diagram>
find_positions(
    const musical::core::pitch_t& pitch,
    const std::string& chord_name
);

// ------------------------------------------------------------
// FIND POSITIONS (pitch + chord_name + shape)
// ------------------------------------------------------------
std::vector<Diagram>
find_positions(
    const musical::core::pitch_t& pitch,
    const std::string& chord_name,
    Diagram::CAGED shape
);

// ------------------------------------------------------------
// FIND ALL POSITIONS (chord_name)
// ------------------------------------------------------------
std::vector<Diagram>
find_all_positions(
    const std::string& chord_name
);
// ------------------------------------------------------------
// FIND ALL DIAGRAMS
// ------------------------------------------------------------
std::vector<Diagram>
find_all_diagrams();

// ------------------------------------------------------------
// RANDOM CHORD NAME
// ------------------------------------------------------------
std::string get_random_chord_name();

// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<std::string, Diagram>
get_random_diagram();

} // namespace chord::database::queries::open