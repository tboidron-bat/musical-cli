#pragma once

#include <vector>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/ChordType.h>

#include <musical/instruments/guitar/six_strings/MovableShapeDiagram.h>
#include <musical/instruments/guitar/six_strings/SixStringsDiagram.h>

namespace musical::instruments::guitar::six_strings::db_movable_queries
{
std::vector<MovableShapeDiagram> find_movable_positions(
    const musical::core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
);

std::vector<MovableShapeDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape);


} // namespace musical::instruments::guitar::six_strings::db_movable_queries