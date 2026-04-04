#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

namespace chord::db
{

    using IntervalMask = uint64_t;

    using movable_diagram_map =
        std::unordered_map<IntervalMask, std::vector<Diagram>>;

    // ------------------------------------------------------------
    // Global DB
    // ------------------------------------------------------------
    const movable_diagram_map& data_movable();

} // namespace chord::db