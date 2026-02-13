#pragma once

#include <optional>
#include <vector>

#include <musical/Core/note/Note.h>
#include <musical/io/note/input/Lexer.h>

namespace musical::io::note
{
    struct pitch_t
    {
        musical::core::Note::Name name;
        musical::core::Note::Accidental accidental;
    };

    class Parser
    {
    public:
        /**
         * @brief Parse une séquence de tokens représentant une note.
         *
         * Grammaire supportée :
         *
         *     NOTE := NAME ACCIDENTAL?
         *
         * Retourne std::nullopt si la séquence est invalide.
         */    
        std::optional<pitch_t> 
        parse(const std::vector<token_t>& tokens);
    private:

        static std::optional<musical::core::Note::Name>
        to_name(std::string_view text);

        // Conversion interne texte → Accidental
        static std::optional<musical::core::Note::Accidental>
        to_accidental(std::string_view text);        
    };
}


    /*
     * @brief Crée une note à partir d'une chaîne de caractères
     * 
     * La chaîne doit être en notation anglo-saxonne : "c", "g#", "bb"
     * 
     * l’altération est détectée depuis la chaîne.
     * 
     * 
     * @throws std::invalid_argument si la chaîne n’est pas reconnue
     */
    
	// core::Note parse_from_saxon(
        // const std::string&,
        // uint8_t default_octave = 4,
        // core::Figure default_figure = core::Figure::Type::QUARTER);

