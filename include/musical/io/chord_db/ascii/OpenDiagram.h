#pragma once

#include <musical/chord_db/OpenChordDiagram.h>

#include <ostream>
#include <cstdint>

namespace chord::db {

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