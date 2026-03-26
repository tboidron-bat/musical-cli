#pragma once

#include <musical/guitar_chord_database/open/database.h>

namespace chord::database
{

    // ------------------------------------------------------------
    // TRIADES
    // ------------------------------------------------------------
    constexpr uint64_t TRIAD_SUS4 = (1ULL << 5) | (1ULL << 7); // 1 4 5
    constexpr uint64_t TRIAD_SUS4_NO5 = TRIAD_SUS4 & ~(1ULL<<7);        

    const open_diagram_map& sus4_open();

} // namespace chord::database