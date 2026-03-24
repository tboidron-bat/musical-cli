#pragma once

#include <musical/guitar_chord_database/open/database.h>

namespace chord::database
{
    constexpr uint64_t TRIAD_MAJ = (1ULL<<4) | (1ULL<<7);
    constexpr uint64_t TRIAD_MAJ_NO5 = TRIAD_MAJ & ~(1ULL<<7);    

    const open_diagram_map&maj_open();
} // namespace chord::database