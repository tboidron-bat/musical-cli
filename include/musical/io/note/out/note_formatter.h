#pragma once

#include <string>
#include <array>
#include <string_view>

#include <musical/Core/pitch_t.h>

namespace musical::io::note::formatter 
{

    /**
     *  Convertit  "do", "ré#" ou "mib" en
     *  "c", "d#", "eb". etc ...
     */
    std::string to_saxon(const std::string&);  
    
    /**
     *  Convertit "c", "d#", "eb"
     *  en  : "do", "ré#", "mib". etc ...
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