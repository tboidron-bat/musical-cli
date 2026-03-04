#pragma once

#include <musical/instruments/guitar/six_strings/OpenChordDiagram.h>

#include <ostream>
#include <cstdint>

namespace musical::instruments::guitar::six_strings {

// ------------------------------------------------------------------
// Dessin du sillet
//
// ===========
// ------------------------------------------------------------------

std::ostream& draw_nut(std::ostream& os, uint8_t string_count);


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