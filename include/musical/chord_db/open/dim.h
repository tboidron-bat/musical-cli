#pragma once

#include <musical/chord_db/open/database.h>

namespace chord::db
{

    // ------------------------------------------------------------
    // TRIADES
    // ------------------------------------------------------------
    constexpr uint64_t TRIAD_DIM = (1ULL << 3) | (1ULL << 6); // 1 b3 b5

    const open_diagram_map& dim_open();

} // namespace chord::db