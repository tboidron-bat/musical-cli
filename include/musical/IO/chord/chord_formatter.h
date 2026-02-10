#pragma once

#include <string>

namespace musical
{
    class Chord;
}

namespace musical::chord_formatter 
{
    /**
     * @brief
     * Retourne une représentation textuelle linéaire d'un accord.
     *
     *  Exemple :
     *  (E, G#, B) = E
     */    
	std::string to_string(const Chord&chord); 


    
    /**
     * @brief Traduction du nom d’un accord de l’anglais vers le français.
     *
     * Exemples :
     *   - "maj"  → "M"
     *   - "min"  → "m"
     *   - "dim"  → "dim"
     *   - "aug"  → "aug"
     *
     */
    std::string to_fr(const std::string&);  
    

    /**
     * @brief Traduction du nom d’un accord du français vers l’anglais.
     *
     * Exemples :
     *   - "M"    → "maj"
     *   - "m"    → "min"
     *   - "dim"  → "dim"
     *   - "aug"  → "aug"
     *
     */        
    std::string to_en(const std::string&);                


}