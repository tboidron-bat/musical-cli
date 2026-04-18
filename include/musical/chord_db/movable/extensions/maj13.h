#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // MAJ13
    // ------------------------------------------------------------
    // Intervalles (root implicite) :
    // 4  → major third
    // 7  → perfect fifth (souvent omise en pratique)
    // 11 → major seventh (7M)
    // 14 → ninth (9)
    // 21 → thirteenth (13)
    //
    // Remarque :
    // - les voicings guitare omettent souvent la quinte
    // - accords souvent "rootless" pour jouabilité

    // ------------------------------------------------------------
    // DATABASE ACCESS
    // ------------------------------------------------------------

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    maj13_movable();

} // namespace chord::db