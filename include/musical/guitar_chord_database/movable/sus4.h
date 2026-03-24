#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{
    // ------------------------------------------------------------
    // SUSPENDED 4
    // ------------------------------------------------------------
    // 1 - 4 - 5 → (5, 7)
    constexpr uint64_t SUS4 = (1ULL << 5) | (1ULL << 7);

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    sus4_movable();

} // namespace chord::database