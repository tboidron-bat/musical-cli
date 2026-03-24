#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{

    using IntervalMask = uint64_t;

    using movable_diagram_map =
        std::unordered_map<IntervalMask, std::vector<Diagram>>;

    // ------------------------------------------------------------
    // Global DB
    // ------------------------------------------------------------
    const movable_diagram_map& data_movable();

} // namespace chord::database