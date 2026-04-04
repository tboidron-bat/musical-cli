#pragma once

#include <ostream>

namespace chord::db {

class OpenChordDiagram;

/* affichage ASCII du diagramme */
std::ostream& operator<<(std::ostream& os,
                         const OpenChordDiagram& diagram);

}