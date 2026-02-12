#include <string>
#include <musical/Core/note/Note.h>


#include <musical/io/common/const_notations.h>

namespace musical::io::note::formatter 
{
    /**
     * @brief
     * Retourne une représentation textuelle linéaire d'une note.
     *
     */    

	std::string to_string(const core::Note&note); 

    /**
     * @brief Retourne la liste des 12 notes chromatiques avec altérations en bémol (ex: "c", "d♭", "d", ...)
     */

    /**
    * @brief Convertit un nom de note en notation latine 
    *   
    *   comme : "do", "ré#" ou "mib" 
    *   en sa représentation anglo-saxonne équivalente 
    *   comme : "c", "d#", "eb").
    *
    *
    *   ATTTENTION à l’encodage utilisé, pour éviter des avertissements ou erreurs liés aux caractères multi-octets.
    *   g++ warning: multi-character character constant [-Wmultichar]
    *       if (c == 'é') c = 'e';
    *
    */
   
    std::string to_saxon(const std::string&);  


    /**
    * @brief Convertit un nom de note musicale en notation anglo-saxonne vers sa notation latine équivalente.
    * 
    * convertit une notation anglo-saxonne, 
    *   ex : 
    *       "c", "d#", "eb", 
    *   en notation latine,
    *   ex : 
    *       "do", "ré#", "mib".
    * 
    *  attention à la gestion des caractères accentués
    */

    std::string to_latin(const std::string&); 



    inline std::array<std::string,12> all_with_flat()
    {
        return {
            "c", "db", "d", "eb", "e", "f",
            "gb", "g", "ab", "a", "bb", "b"
        };
    }

    inline std::array<std::string,12> all_with_sharp()
    {
        return {
            "c", "c#", "d", "d#", "e", "f",
            "f#", "g", "g#", "a", "a#", "b"
        };
    }


}