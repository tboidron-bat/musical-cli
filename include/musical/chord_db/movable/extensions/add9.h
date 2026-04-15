#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // ADD9
    // ------------------------------------------------------------
    // Intervalles :
    // 0 (root implicite)
    // 4 (major third)
    // 7 (perfect fifth)
    // 2 (9th, i.e. 14 semitones → 2 mod 12)
    //
    // Remarque :
    // - add9 ≠ 9 (pas de 7e)
    // - on reste sur une triade enrichie



    using IntervalMask = uint64_t;

    /**
     * Voicings add9 (formes déplaçables)
     *
     * Exemples typiques :
     *   Cadd9 : x32030
     *   Dadd9 : xx0230
     *
     * Notes :
     * - la fondamentale est implicite (Diagram gère le root)
     * - certaines formes peuvent omettre la quinte
     */
    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    add9_movable();

} // namespace chord::db