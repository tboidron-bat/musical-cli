#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <ostream>

namespace musical::io::note
{

struct token_t
{
    enum class TokenKind
    {
        NAME,
        ACCIDENTAL
    };

    TokenKind kind;
    std::string text;   // slice de la chaîne analysée
};

// ------------------------------------------------------------
// Définition de lexèmes (règles)
// ------------------------------------------------------------
struct lexeme_def
{
    std::string_view text;
    token_t::TokenKind kind;
};

inline constexpr std::array<lexeme_def, 18> lexemes =
{{
    // --- FR (longs d'abord)
    { "sol", token_t::TokenKind::NAME },
    { "do",  token_t::TokenKind::NAME },
    { "re",  token_t::TokenKind::NAME },
    { "mi",  token_t::TokenKind::NAME },
    { "fa",  token_t::TokenKind::NAME },
    { "la",  token_t::TokenKind::NAME },
    { "si",  token_t::TokenKind::NAME },

    // --- Saxon
    { "c", token_t::TokenKind::NAME },
    { "d", token_t::TokenKind::NAME },
    { "e", token_t::TokenKind::NAME },
    { "f", token_t::TokenKind::NAME },
    { "g", token_t::TokenKind::NAME },
    { "a", token_t::TokenKind::NAME },
    { "b", token_t::TokenKind::NAME },

    // --- Accidentals (2 chars d'abord)
    { "##", token_t::TokenKind::ACCIDENTAL },
    { "bb", token_t::TokenKind::ACCIDENTAL },
    { "#",  token_t::TokenKind::ACCIDENTAL },
    { "b",  token_t::TokenKind::ACCIDENTAL }    
}};

/**
 * @brief Helper permettant de détecter une note
 *        (nom + altération optionnelle).
 *
 * ⚠️ L’entrée est supposée être déjà normalisée
 *    en ASCII minuscule (via normalize_to_ascii).
 *
 * Cette classe :
 *   - ne valide pas musicalement
 *   - ne construit pas de pitch
 *   - ne gère pas l’UTF-8
 *
 * Elle se contente d’identifier la structure :
 *   NAME + ACCIDENTAL optionnel
 */
class NoteLexer
{
public:

    /**
     * @brief Retourne la longueur (en caractères ASCII)
     *        d'une note valide en début de chaîne.
     *
     * Exemple :
     *   "c#maj7" → 2
     *   "solbb"  → 5
     *   "xmaj7"  → 0
     */
    static size_t
    parse_note_length(std::string_view normalized_input);

    /**
     * @brief Découpe une note en tokens.
     *
     * L'entrée doit être normalisée (ASCII minuscule).
     */
    static std::vector<token_t>
    tokenize(std::string_view normalized_input);
};

std::ostream& operator<<(std::ostream&, const token_t&);

} // namespace musical::io::note