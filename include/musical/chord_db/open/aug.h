#pragma once

#include <musical/chord_db/open/database.h>

namespace chord::db
{

    constexpr uint64_t TRIAD_AUG = (1ULL << 4) | (1ULL << 8); 

    const open_diagram_map& aug_open();

} // namespace chord::db