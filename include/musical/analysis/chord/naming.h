#pragma once

#include <string>
#include <vector>

namespace musical::core::chord {
    class Chord;
    class ChordType;
}

namespace musical::analysis::chord {

    std::string find_name(
        const musical::core::chord::ChordType& type);

    // ─────────────────────────────
    // Analyses spécialisées
    // ─────────────────────────────

    // std::string
    // analyse_dyad(const musical::core::chord::Chord& chord);

    // std::string
    // analyse_triad(const musical::core::chord::Chord& chord);

    // std::string
    // analyse_tetrade(const musical::core::chord::Chord& chord);

} // namespace musical::analysis::chord
