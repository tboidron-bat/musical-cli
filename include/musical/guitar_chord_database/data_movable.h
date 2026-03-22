#pragma once

#include <map>
#include <vector>

#include <musical/Core/chord/ChordType.h>
#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{


/**
 * Les diagrammes sont définis en coordonnées relatives (offset).
 * Aucun fret absolu n'est stocké ici.
 *
 * Exemple de génération :
 *
 *   auto shape = database_movable().at(chord_type);
 *   auto concrete = shape[0].generate(barre_fret);
 */
const std::map<std::string,std::vector<Diagram>>
& data_movable();
} //chord::database