#pragma once

#include <string>

namespace musical::core::chord {
    class Chord;
}

namespace musical::instruments::guitar::six_strings {
    class ChordDiagram;
}

namespace io::instruments::guitar::six_strings::chord_diagram {

/**
 * Génère une représentation ASCII d’un accord
 * pour guitare 6 cordes en accordage standard.
 */
std::string 
to_ascii(const musical::core::chord::Chord& chord);

/**
 * Génère une représentation ASCII directe
 * depuis un diagramme guitare 6 cordes.
 *
 * Utilisé notamment pour l’option CLI --all.
 */
std::string 
to_ascii(const musical::instruments::guitar::six_strings::ChordDiagram& diagram);

} // namespace io::instruments::guitar::chord_diagram6strings
