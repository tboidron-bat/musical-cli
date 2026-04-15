#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // MAJ7
    // ------------------------------------------------------------

    // Remarque :
    // - accord stable / tonal
    // - base des extensions maj9, maj13
    // - souvent utilisé en voicings rootless


    // ------------------------------------------------------------
    // DATABASE ACCESS
    // ------------------------------------------------------------

    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    maj7_movable();

} // namespace chord::db