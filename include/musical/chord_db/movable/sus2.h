#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // TRIADES / SUSPENDED
    // ------------------------------------------------------------
    constexpr uint64_t SUS2 = (1ULL << 2) | (1ULL << 7);

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    sus2_movable();

} // namespace chord::db