#pragma once

#include <string>

namespace musical::core {
    class Chord;
}

namespace musical::chord::guitar {
    template <size_t N_STRINGS>
    class Diagram;
}

namespace musical::chord::guitar::diagram_ascii_6 {

/**
 * Génère une représentation ASCII d’un accord
 * pour guitare 6 cordes en accordage standard.
 */
std::string to_ascii(const musical::core::Chord& chord);

/**
 * Génère une représentation ASCII directe
 * depuis un diagramme guitare 6 cordes.
 *
 * Utilisé notamment pour l’option CLI --all.
 */
std::string to_ascii(const musical::chord::guitar::Diagram<6>& diagram);

} // namespace musical::chord::guitar::diagram_ascii_6
