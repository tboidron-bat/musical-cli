#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // DOMINANT 7
    // ------------------------------------------------------------
    // Intervalles (root implicite) :
    // 4  → major third
    // 7  → perfect fifth
    // 10 → minor seventh (b7)
    //
    // Remarque :
    // - accord de dominante (très utilisé en tonalité)
    // - base des accords étendus (9, 11, 13)

    using IntervalMask = uint64_t;

    // ------------------------------------------------------------
    // DATABASE ACCESS
    // ------------------------------------------------------------

    /**
     * Voicings de dominante 7 (formes CAGED)
     *
     * Contient :
     * - formes complètes (avec quinte)
     * - formes rootless / sans quinte
     */
    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    dominant7_movable();

} // namespace chord::db