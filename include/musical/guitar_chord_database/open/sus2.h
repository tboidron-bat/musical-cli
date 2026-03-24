#pragma once

#include <musical/guitar_chord_database/open/database.h>

namespace chord::database
{

    // ------------------------------------------------------------
    // TRIADES
    // ------------------------------------------------------------
    constexpr uint64_t TRIAD_SUS2 = (1ULL << 2) | (1ULL << 7); // 1 2 5

    const open_diagram_map& sus2_open();

} // namespace chord::database