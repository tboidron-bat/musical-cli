#pragma once

#include <string>
#include <vector>

namespace musical::core {
    class Chord;
}

namespace musical::analysis::chord_name {

    /**
     * @brief Proposition de nom pour un accord analysé.
     */
    struct candidate
    {
        // Ex : "Em7", "C6", "F#ø", etc.
        std::string name;

        /* Pertinence de l’analyse :
           10 → interprétation canonique / évidente
           8–9 → très plausible (renversement, omission mineure)
           5–7 → alternative valide selon contexte
           1–4 → hypothèse faible / théorique
           0 → bruit (à ignorer)
        */
        int score = 0;
    };

    /**
     * @brief Analyse harmonique d’un accord abstrait
     *        et retourne une liste de noms candidats.
     *
     * L’accord fourni :
     *  - possède déjà une tonique
     *  - possède déjà des intervalles relatifs
     *  - est indépendant de toute réalisation (voicing, octave, etc.)
     */
    std::vector<candidate> find(const musical::core::Chord& chord);

    // ─────────────────────────────
    // Analyses spécialisées
    // ─────────────────────────────

    std::vector<candidate>
    analyse_dyad(const musical::core::Chord& chord);

    std::vector<candidate>
    analyse_triad(const musical::core::Chord& chord);

    std::vector<candidate>
    analyse_tetrade(const musical::core::Chord& chord);

} // namespace musical::analysis::chord_name
