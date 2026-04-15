#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // MAJOR TRIAD FAMILY
    // ------------------------------------------------------------
    // Intervalles (root implicite) :
    // 4  → major third
    // 7  → perfect fifth

    using IntervalMask = uint64_t;

    // ------------------------------------------------------------
    // DATABASE ACCESS
    // ------------------------------------------------------------

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    maj_movable();

} // namespace chord::db