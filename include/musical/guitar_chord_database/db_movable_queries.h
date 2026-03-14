#pragma once

#include <vector>
#include <utility>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/ChordType.h>

#include <musical/guitar_chord_database/MovableShapeDiagram.h>
#include <musical/guitar_chord_database/SixStringsDiagram.h>

namespace chord::database::queries::movable
{
std::vector<MovableShapeDiagram> find_all_positions(
    const musical::core::chord::ChordType& chord_type
);
std::vector<MovableShapeDiagram> find_positions(
    const musical::core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
);
std::vector<MovableShapeDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape);

std::pair<
    musical::core::chord::ChordType,
    MovableShapeDiagram
    >
get_random_diagram();

} // namespace chord::database::queries::movable