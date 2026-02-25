#pragma once

#include <map>
#include <vector>

#include <musical/instruments/guitar/six_strings/ChordDiagram.h>
#include <musical/Core/chord/ChordType.h>

namespace musical::instruments::guitar::six_strings
{

using DiagramMap = std::map<
    musical::core::chord::ChordType,
    std::vector<ChordDiagram>
>;

const DiagramMap& database_shape_d();

} // namespace musical::instruments::guitar::six_strings