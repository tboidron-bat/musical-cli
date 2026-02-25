#pragma once

#include <string>
#include <array>
#include <string_view>

#include <musical/Core/pitch_t.h>

namespace musical::io::note::formatter 
{
    /**
     * @brief
     * Retourne une représentation textuelle linéaire d'un pitch.
     */
    std::string to_string(const musical::core::pitch_t& pitch); 


    /**
     * @brief Convertit un nom de note en notation latine 
     * comme : "do", "ré#" ou "mib" 
     * vers sa représentation anglo-saxonne équivalente 
     * comme : "c", "d#", "eb".
     */
    std::string to_saxon(const std::string&);  


    /**
     * @brief Convertit une notation anglo-saxonne
     * ex : "c", "d#", "eb"
     * vers notation latine : "do", "ré#", "mib"
     */
    std::string to_latin(const std::string&); 


    inline constexpr std::array<std::string_view,12> all_with_flat()
    {
        return {
            "c", "db", "d", "eb", "e", "f",
            "gb", "g", "ab", "a", "bb", "b"
        };
    }

    inline constexpr std::array<std::string_view,12> all_with_sharp()
    {
        return {
            "c", "c#", "d", "d#", "e", "f",
            "f#", "g", "g#", "a", "a#", "b"
        };
    }

} // namespace musical::io::note::formatter