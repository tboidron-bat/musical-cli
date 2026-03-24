#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{

    // ------------------------------------------------------------
    // TRIADES DIMINUÉES
    // ------------------------------------------------------------
    // 1 - b3 - b5 → (3, 6)
    constexpr uint64_t TRIAD_DIM = (1ULL << 3) | (1ULL << 6);

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    dim_movable();

} // namespace chord::database



