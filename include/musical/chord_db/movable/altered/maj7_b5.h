#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    // ------------------------------------------------------------
    // ▲♭5 / ▲#11
    // ------------------------------------------------------------
    //
    // Remarque :
    // - ♭5 ≡ #11 (même Tone class, rôle harmonique différent)
    // - couleur lydienne / altérée
    // - souvent utilisé en jazz / musique modale

     /**
     * Voicings ▲♭5 / ▲#11
     *
     * Contient :
     * - voicings avec ♭5 direct
     * - voicings avec #11 étendue
     */
    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    maj7_b5_movable();

} // namespace chord::db