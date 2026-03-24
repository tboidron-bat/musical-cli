#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{

    // ------------------------------------------------------------
    // TRIADES AUGMENTÉES
    // ------------------------------------------------------------
    // 1 - 3 - #5  → (4, 8)
    constexpr uint64_t TRIAD_AUG = (1ULL << 4) | (1ULL << 8);

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    aug_movable();

} // namespace chord::database

