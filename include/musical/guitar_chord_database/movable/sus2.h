#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{
    // ------------------------------------------------------------
    // TRIADES / SUSPENDED
    // ------------------------------------------------------------
    constexpr uint64_t SUS2 = (1ULL << 2) | (1ULL << 7);

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    sus2_movable();

} // namespace chord::database