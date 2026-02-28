#pragma once

#include <string>

namespace musical::core::chord {
    class Chord;
}

namespace musical::instruments::guitar::six_strings {
    class OpenChordDiagram;
}

namespace io::guitar::six_strings {

/**
 * Génère une représentation ASCII d’un accord
 * pour guitare 6 cordes en accordage standard.
 */
std::string 
open_chord_diagram_to_ascii(const musical::core::chord::Chord& chord);

/**
 * Génère une représentation ASCII directe
 * depuis un diagramme guitare 6 cordes.
 *
 * Utilisé notamment pour l’option CLI --all.
 */
std::string 
open_chord_diagram_to_ascii(const musical::instruments::guitar::six_strings::OpenChordDiagram& diagram);

} // namespace io::instruments::guitar::chord_diagram6strings
