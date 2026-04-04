#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

namespace chord::db
{

    // ------------------------------------------------------------
    // TRIADES
    // ------------------------------------------------------------
    constexpr uint64_t TRIAD_MIN = (1ULL << 3) | (1ULL << 7);
    constexpr uint64_t TRIAD_MIN_NO5 = TRIAD_MIN & ~(1ULL << 7);

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    min_movable();

} // namespace chord::db