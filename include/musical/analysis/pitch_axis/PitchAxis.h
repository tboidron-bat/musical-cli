#pragma once

#include <musical/core/Tone.h>

namespace musical::analysis::pitch_axis
{

/**
 * Pitch Axis System (PAS)
 * -----------------------
 *
 * Le Pitch Axis est une technique harmonique où une note centrale (axis)
 * reste perceptivement stable, tandis que les accords autour peuvent
 * provenir de différentes tonalités ou modes.
 *
 * Contrairement à l’harmonie tonale classique :
 * - on ne fixe pas une tonalité unique
 * - on ne suit pas forcément des fonctions (tonique, dominante, etc.)
 *
 * À la place :
 * - on fixe une classe de hauteur (Tone)
 * - on sélectionne ou génère des accords qui "gravitent" autour de cette note
 *
 * Dans cette implémentation :
 * - axis est un core::Tone class (0–11)
 * - indépendante de l’octave
 * - indépendante de l’enharmonie (Cs == Df)
 *
 * Exemple :
 *   axis = C
 *   accords possibles :
 *     Cmaj (C E G)
 *     Fmaj (F A C)
 *     Abmaj (Ab C Eb)
 *     Amin (A C E)
 *
 * Tous contiennent la note C → cohérence perceptive
 */

struct PitchAxisContext
{
    core::Tone axis;
};


/**
 * =========================
 * TODO (implémentation future)
 * =========================
 *
 * [1] Détection basique
 * ---------------------
 * Implémenter :
 *
 *   bool contains_axis(const Chord&, Tone axis);
 *
 * -> retourne true si l’accord contient la pitch class axis
 *
 *
 * [2] Générateur simple (MVP)
 * --------------------------
 * Parcourir tous les accords connus (ChordFactory)
 * et filtrer ceux qui contiennent axis
 *
 *   std::vector<Chord> generate(axis)
 *
 *
 * [3] Générateur basé sur les gammes (recommandé)
 * ----------------------------------------------
 * Pour chaque :
 *   - root (12 tons)
 *   - mode (Ionian, Dorian, etc.)
 *
 *   scale = ScaleKeyed(root, mode)
 *   chords = Harmonizer(scale)
 *
 *   garder les accords tels que :
 *     axis ∈ scale
 *     ou axis ∈ chord
 *
 *
 * [4] Stratégies de sélection (important)
 * --------------------------------------
 * Ajouter une policy :
 *
 *   enum AxisPolicy {
 *       STRICT_CONTAIN,    // axis ∈ chord
 *       SCALE_COMPATIBLE,  // chord issu d’une gamme contenant axis
 *       LOOSE              // tolérance (approche perceptive)
 *   };
 *
 *
 * [5] Construction de progression
 * ------------------------------
 * Créer un builder :
 *
 *   PitchAxisProgressionBuilder
 *
 * Objectif :
 *   - éviter listes aléatoires
 *   - organiser les accords par "couleur modale"
 *   - alterner diatonique / exotique
 *
 *
 * [6] Intégration guitare
 * ----------------------
 * Filtrer les accords générés avec :
 *
 *   chord_db (open / movable)
 *
 * pour garantir :
 *   - jouabilité
 *   - voicings cohérents
 *
 *
 * [7] CLI
 * -------
 * Ajouter option :
 *
 *   chord --axis C
 *
 * éventuellement :
 *
 *   chord --axis C --play
 *
 *
 * [8] Extension avancée
 * --------------------
 * Autoriser accords SANS axis mais compatibles :
 *
 * ex :
 *   G7 → résout vers C
 *
 * => notion de "gravité harmonique"
 *
 */

}