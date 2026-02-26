#pragma once

#include <string>

namespace musical::core::chord
{
    class Chord;
}

namespace musical::io::chord::formatter 
{
    /**
     * @brief
     * Retourne une représentation textuelle linéaire d'un accord.
     *
     * Exemple :
     *   C(4,7) (C, E, G) = C
     */
    std::string to_string(
        const musical::core::chord::Chord& chord
    );

    /**
     * @brief Traduction du nom d’un accord de l’anglais vers le français.
     */
    std::string to_fr(const std::string& name_en);

    /**
     * @brief Traduction du nom d’un accord du français vers l’anglais.
     */
    std::string to_en(const std::string& name_fr);

}