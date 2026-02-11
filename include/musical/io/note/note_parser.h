#include <musical/Core/note/Note.h>

#include <string>

namespace musical::io::note
{
    
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
    
	core::Note parse_from_saxon(
        const std::string&,
        uint8_t default_octave = 4,
        Figure default_figure = FigureType::QUARTER);
}
