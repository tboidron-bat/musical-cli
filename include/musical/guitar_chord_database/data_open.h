#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{
using diagram_map = std::unordered_map<
    std::string,
    std::vector<Diagram>
>;

const diagram_map& database_open();

} // namespace chord::database