#ifndef __CHORDFUNCTIONANALER_H__
#define __CHORDFUNCTIONANALER_H__

#include <string>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/ScaleKeyed.h>

namespace musical::Analysis {

/**
 * Classe utilitaire pour analyser la fonction harmonique d’un accord
 * dans une tonalité donnée (gamme).
 */

class ChordFunctionAnalyser
{
public:
    /**
     * @brief Déduit la fonction harmonique de l'accord dans une gamme donnée.
     * 
     * @param chord Accord à analyser.
     * @param gamme ScaleKeyed/tonalité de référence (ex : do majeur, la mineur…).
     * @return Chaîne représentant la fonction harmonique (ex : "I", "ii", "V7", "vi°", etc.).
     */
    static std::string to_string(
        const musical::Chord& chord, 
        const musical::ScaleKeyed& gamme);
};

} // namespace musical::Analysis

#endif

