#pragma once

#include <string_view>
#include <vector>

#include <musical/io/chord/tokens.h>

namespace musical::io::chord
{

/**
 * @brief Découpe une chaîne représentant un accord
 *        en une suite de tokens lexicaux.
 *
 * Exemple :
 *   "C#m7b5/G#"
 *
 * Produira :
 *   ROOT("C#")
 *   LEXEME("m")
 *   LEXEME("7")
 *   LEXEME("b5")
 *   SLASH("/")
 *   ROOT("G#")
 *
 * Le lexer :
 *   - ne valide pas l’accord
 *   - n’interprète pas l’harmonie
 *   - ne construit pas de ChordSpec
 *
 * Il se contente de découper la chaîne.
 */
class Lexer
{
public:

    /**
     * @brief Tokenize une chaîne d'accord.
     *
     * @param input Chaîne d'entrée (ex: "Cmaj7")
     * @return Liste des tokens détectés
     */
    static std::vector<Token> tokenize(std::string_view input);
};

} // namespace musical::io::chord
