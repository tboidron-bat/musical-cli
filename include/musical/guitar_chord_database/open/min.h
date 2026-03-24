#pragma once

#include <musical/guitar_chord_database/open/database.h>

namespace chord::database
{
    constexpr uint64_t TRIAD_MIN = (1ULL << 3) | (1ULL << 7);
    constexpr uint64_t TRIAD_MIN_NO5 = TRIAD_MIN & ~(1ULL << 7);

    const open_diagram_map&min_open();

} // namespace chord::database





