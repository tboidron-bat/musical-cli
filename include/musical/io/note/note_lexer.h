#pragma once

#include <string_view>
#include <optional>

namespace musical::io::note
{

    struct token_t
    {
        char letter;      // A–G
        int accidental;   // -2, -1, 0, +1, +2
        std::string_view lexeme;
    };

    class Lexer
    {
    public:
        static std::optional<token_t>
            parse(std::string_view input);
    };

    /**
     * @brief Normalise une chaîne représentant une note, en appliquant des règles de formatage ou de conversion.
     * 
     * Par exemple, convertir des majuscules en minuscules, ou uniformiser les altérations.
     * 
     * @return Chaîne normalisée
     */
    
    std::string normalize_name(const std::string&);   


}
