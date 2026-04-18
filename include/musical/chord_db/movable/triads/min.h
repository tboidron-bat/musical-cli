#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // MINOR TRIAD FAMILY
    // ------------------------------------------------------------
    // Intervalles (root implicite) :
    // 4  → minor third
    // 7  → perfect fifth

    // ------------------------------------------------------------
    // DATABASE ACCESS
    // ------------------------------------------------------------
    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    min_movable();

} // namespace chord::db