#pragma once

#include <vector>

#include <musical/Core/pitch_t.h>
#include <musical/Core/chord/ChordType.h>

#include <musical/instruments/guitar/six_strings/ChordDiagram.h>

namespace guitar::six_strings::chord_diagram::database_queries
{
    using namespace musical::instruments::guitar::six_strings;

// ------------------------------------------------------------
// Position kind
// ------------------------------------------------------------
enum class PositionKind
{
    OPEN,
    MOVABLE,
    ALL
};

// ------------------------------------------------------------
// Find open positions only
// ------------------------------------------------------------
std::vector<ChordDiagram> find_open_position(
    const musical::core::pitch_t pitch,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape
);

// ------------------------------------------------------------
// Find movable (non open) positions only
// ------------------------------------------------------------
std::vector<ChordDiagram> find_movable_position(
    const musical::core::pitch_t pitch,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape
);

// ------------------------------------------------------------
// Generic position search
// ------------------------------------------------------------
std::vector<ChordDiagram> find_positions(
    const musical::core::pitch_t pitch,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape,
    PositionKind kind
);

// ------------------------------------------------------------
// Random diagram (from all shapes)
// ------------------------------------------------------------
ChordDiagram get_random_diagram();

} // namespace musical::instruments::guitar::six_strings


// std::vector<ChordDiagram> find_open_posistion(
//     const musical::core::pitch_t pitch,       
//     const ChordType& chord_type,
//     ChordDiagram::CAGEDShape shape
//     )    
// {
//     std::vector<ChordDiagram> results;
//     //1)Parcourir toutes les base de donnees.
//     //2)if !is_open_chord() 
//     //    continue;
//     // else if diagram contains the chord type
//     //{
//     //    verifier que la tonique du diagramme correspond au pitch recherche
//     //    if (tonique != pitch)
//     //        continue;
//     //    else
//     //        ajouter le diagramme a la liste des resultats   
//     //}


//     return results;   
// }
// std::vector<ChordDiagram> find_movable_position(
//     const musical::core::pitch_t pitch,       
//     const ChordType& chord_type,
//     ChordDiagram::CAGEDShape shape
//     )    
// {
//     std::vector<ChordDiagram> results;
//     //1)Parcourir toutes les base de donnees.
//     //2)if !is_open_chord() 
//     //    continue;
//     //2)if diagram contains the chord type
//     //{
//     //    verifier que la tonique du diagramme correspond au pitch recherche
//     //    if (tonique != pitch)
//     //        continue;
//     //    else
//     //        ajouter le diagramme a la liste des resultats   
//     //}

//     return results;
// }

// ChordDiagram get_hasard_diagram()
// {

// }