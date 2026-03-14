#pragma once

#include <vector>
#include <utility>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/ChordType.h>

#include <musical/guitar_chord_database/OpenChordDiagram.h>
#include <musical/guitar_chord_database/SixStringsDiagram.h>

namespace chord::database::queries::open
{
std::vector<OpenChordDiagram> find_all_positions(
    const musical::core::pitch_t& pitch,
    const musical::core::chord::ChordType& chord_type
);
std::vector<OpenChordDiagram> find_positions(
    const musical::core::pitch_t& pitch,
    const musical::core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
);
std::vector<OpenChordDiagram> find_all_diagrams();
// ------------------------------------------------------------
// RANDOM CHORDTYPE
// ------------------------------------------------------------
musical::core::chord::ChordType get_random_chord_type();
// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<
    musical::core::chord::ChordType,
    OpenChordDiagram
    >
get_random_diagram();
} // namespace chord::database::queries::open