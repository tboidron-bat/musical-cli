#pragma once

#include <map>
#include <vector>

#include <musical/instruments/guitar/six_strings/OpenChordDiagram.h>
#include <musical/Core/chord/ChordType.h>

namespace musical::instruments::guitar::six_strings
{

using DiagramMap = std::map<
    musical::core::chord::ChordType,
    std::vector<OpenChordDiagram>
>;

const DiagramMap& database_open_e();

} // namespace musical::instruments::guitar::six_strings