#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // MAJ9
    // ------------------------------------------------------------
    // Intervalles :
    // 0 (root implicite)
    // 4 (major third)
    // 7 (perfect fifth)
    // 11 (major seventh)
    // 14 (ninth)

    constexpr uint64_t MAJ9 =
        (1ULL << 4)  | // major third
        (1ULL << 7)  | // perfect fifth
        (1ULL << 11) | // major seventh
        (1ULL << 14);  // ninth

    using IntervalMask = uint64_t;

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    maj9_movable();

} // namespace chord::db