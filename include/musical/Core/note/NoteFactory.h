#pragma once

#include <musical/Core/note/Note.h>
#include <musical/Core/MusicalCoreEnums.h>
#include <musical/Core/Figure.h>

namespace musical
{
class NoteFactory
{
public:
    /**
     * @brief Crée une note à partir de son index chromatique
     * 
     * 
     */

    static Note create(int chromatic_value, uint8_t default_octave=4, 
        Figure default_figure = FigureType::QUARTER, bool sharp=true);


    /**
     * @brief Crée une note à partir de son nom (lettre), altération et octave
     * 
     * @param name Nom de la note en notation anglo-saxonne (`a` = La, `c` = Do, etc.)
     * @param accid Altération éventuelle (dièse, bémol, etc.)
     * @param octave Octave MIDI (ex : 4 pour le Do central = C4)
     * 
     * @return Note construite avec les paramètres spécifiés
     * 
     * @throws std::invalid_argument si le nom est invalide (non compris entre 'a' et 'g')
     */	
	static Note create(char name,musical::Accidental accid = musical::Accidental::NONE,
		uint8_t octave=4, Figure figure = FigureType::QUARTER);

    /**
     * @brief Crée une note à partir d'une chaîne de caractères
     * 
     * La chaîne doit être en notation anglo-saxonne : "c", "g#", "bb"
     * 
     * L’octave par défaut est fixée à 4, et l’altération est détectée depuis la chaîne.
     * 
     * @param name Nom de la note sous forme de chaîne
     * @return Note correspondante
     * 
     * @throws std::invalid_argument si la chaîne n’est pas reconnue
     */
	static Note create(std::string,uint8_t default_octave = 4,
            Figure default_figure = FigureType::QUARTER);
};
}