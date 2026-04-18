#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // DATABASE ACCESS
    // ------------------------------------------------------------

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    maj13_sus2_movable();

} // namespace chord::db