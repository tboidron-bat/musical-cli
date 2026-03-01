#pragma once

#include <map>
#include <vector>

#include <musical/Core/chord/ChordType.h>
#include <musical/instruments/guitar/six_strings/MovableShapeDiagram.h>

namespace musical::instruments::guitar::six_strings
{

// Type alias cohérent avec ton système existant
using MovableDiagramMap =
    std::map<
        musical::core::chord::ChordType,
        std::vector<MovableShapeDiagram>
    >;

/**
 * @brief Retourne la base des formes déplaçables CAGED forme A.
 *
 * Les diagrammes sont définis en coordonnées relatives (offset).
 * Aucun fret absolu n'est stocké ici.
 *
 * Exemple de génération :
 *
 *   auto shape = database_movable_a().at(chord_type);
 *   auto concrete = shape[0].generate(barre_fret);
 */
const MovableDiagramMap& database_movable_e();

} // namespace musical::instruments::guitar::six_strings