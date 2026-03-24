#pragma once

#include <musical/guitar_chord_database/open/database.h>

namespace chord::database
{

    constexpr uint64_t TRIAD_AUG = (1ULL << 4) | (1ULL << 8); 

    const open_diagram_map& aug_open();

} // namespace chord::database