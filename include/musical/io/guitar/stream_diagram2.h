#pragma once

#include <ostream>

namespace musical::instruments::guitar::six_strings {

class OpenChordDiagram;

/* affichage ASCII du diagramme */
std::ostream& operator<<(std::ostream& os,
                         const OpenChordDiagram& diagram);

}