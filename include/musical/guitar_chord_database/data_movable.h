#pragma once

#include <map>
#include <vector>

#include <musical/Core/chord/ChordType.h>
#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{

using movable_diagram_map =
    std::map<
        std::string,
        std::vector<Diagram>
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
const movable_diagram_map& data_movable();

} //chord::database