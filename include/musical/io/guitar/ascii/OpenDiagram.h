#pragma once

#include <musical/guitar_chord_database/OpenChordDiagram.h>

#include <ostream>
#include <cstdint>

namespace chord::database {

// ------------------------------------------------------------------
// Affichage ASCII d'un diagramme d'accord guitare
//
// Exemple :
//
// 0 x
// ===========
// | | | | | |
// |2| | | | |
// | |3| | | |
// | | | | | |
// ------------------------------------------------------------------

std::ostream& operator<<(
    std::ostream& os,
    const OpenChordDiagram& diagram);

}