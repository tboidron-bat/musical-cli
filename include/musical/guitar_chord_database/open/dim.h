#pragma once

#include <musical/guitar_chord_database/open/database.h>

namespace chord::database
{

    // ------------------------------------------------------------
    // TRIADES
    // ------------------------------------------------------------
    constexpr uint64_t TRIAD_DIM = (1ULL << 3) | (1ULL << 6); // 1 b3 b5

    const open_diagram_map& dim_open();

} // namespace chord::database