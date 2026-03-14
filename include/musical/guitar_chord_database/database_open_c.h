#pragma once

#include <map>
#include <vector>

#include <musical/guitar_chord_database/OpenChordDiagram.h>
#include <musical/Core/chord/ChordType.h>

namespace chord::database
{
using DiagramMap = std::map<
    musical::core::chord::ChordType,
    std::vector<OpenChordDiagram>
>;

const DiagramMap& database_open_c();

} //chord::database