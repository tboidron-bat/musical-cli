#pragma once

#include <vector>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/ChordType.h>

#include <musical/instruments/guitar/six_strings/OpenChordDiagram.h>
#include <musical/instruments/guitar/six_strings/SixStringsDiagram.h>

namespace musical::instruments::guitar::six_strings::db_open_queries
{

std::vector<OpenChordDiagram> find_open_positions(
    const musical::core::pitch_t& pitch,
    const musical::core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
);

std::vector<OpenChordDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape);

// ------------------------------------------------------------
// Random diagram
// ------------------------------------------------------------
OpenChordDiagram get_random_diagram();

} // namespace musical::instruments::guitar::six_strings::db_open_queries