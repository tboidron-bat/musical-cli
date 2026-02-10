#ifndef NOTESERVICE_H
#define NOTESERVICE_H

/*TODO: Diviser ce fichier en deux avec d un coté:
NoteNotationService ou NoteConversionService
avec 
to_string(const Note&)
from_mei(const std::string&)
to_saxon(const std::string&)
to_latin(const std::string&)
normalize_note_name(const std::string&)
sharp_to_flat(const Note&)
et
de l'autre; NotePitchService ou NoteUtils
avec:
chromatic_index(const Note&)
find(const Note&) (si c’est une recherche dans une gamme)
all_with_flat()
all_with_sharp()
*/

#include <musical/Core/note/Note.h>

#include <string>
#include <array>
#include <cstddef>


namespace musical::NoteService
{
    /**
     * @brief Retourne la liste des 12 notes chromatiques avec altérations en bémol (ex: "c", "d♭", "d", ...)
     */
    std::array<std::string,12> all_with_flat();

    /**
     * @brief Retourne la liste des 12 notes chromatiques avec altérations en dièse (ex: "c", "c#", "d", ...)
     */
    std::array<std::string,12> all_with_sharp();

    /**
     * @brief Retourne une représentation textuelle de la note (ex: "c#", "g", "bb")
     */
    std::string to_string(const Note&);
    /**
     * @brief 
    * Trouver la position de la tonique dans la gamme chromatique 
     */
    size_t find(const musical::Note&);   

    /*
        Entre 0 et 12
    */
    std::size_t chromatic_index(const Note&); 



    /**
     * @brief Normalise une chaîne représentant une note, en appliquant des règles de formatage ou de conversion.
     * 
     * Par exemple, convertir des majuscules en minuscules, ou uniformiser les altérations.
     * 
     * @param note_str Chaîne de la note à normaliser
     * @return Chaîne normalisée
     */
    std::string normalize_note_name(const std::string&);   


    /**
    * Retourne le nom de la note dans le système latin
    * à partir d'une tonalité  MEI: "0","1s", ..., "3f", ..etc..
    */
    std::string from_mei(const std::string&);

    /**
    * @brief Convertit un nom de note en notation latine (ex : "do", "ré#", "mib") 
    *        en sa représentation anglo-saxonne équivalente (ex : "c", "d#", "eb").
    *
    *
    * g++ warning: multi-character character constant [-Wmultichar]
    *         if (c == 'é') c = 'e';
    *
    */
    std::string to_saxon(const std::string&);  

    /**
    * @brief Convertit un nom de note musicale en notation anglo-saxonne vers sa notation latine équivalente.
    * 
    * Cette fonction prend en entrée une chaîne de caractères représentant une note en notation anglo-saxonne,
    * par exemple : "c", "d#", "eb", et retourne la représentation correspondante en notation latine,
    * par exemple : "do", "ré#", "mib".
    * 
    * @note Comme pour la conversion inverse, attention à la gestion des caractères accentués
    *       et à l’encodage utilisé, pour éviter des avertissements ou erreurs liés aux caractères multi-octets.
    */

    std::string to_latin(const std::string&); 



    /**
     * @brief Convertit une note avec dièse (sharp) en sa forme équivalente avec bémol (flat).
     * 
     * Ex : "fa#" -> "solb"
     * 
     * @param sharp_note Nom de la note avec dièse
     * @return Nom de la note équivalente avec bémol
     */
	Note sharp_to_flat(const musical::Note&);	
}

#endif