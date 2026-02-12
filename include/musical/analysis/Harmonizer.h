#pragma once

#include <musical/Core/chord/Chord.h>
#include <musical/Core/scale/ScaleKeyed.h>
#include <musical/Core/chord/Factory.h>

#include <vector>
#include <cstdint>

namespace musical::analysis {

enum class HarmoIntervalType : uint8_t {    

    TIERCE,
    QUARTE,
    QUINTE,
    SIXTE
};    

class Harmonizer {

    HarmoIntervalType _harm_intvl;
    core::ChordClassType _chord_class;

public:
    Harmonizer(
        HarmoIntervalType h = HarmoIntervalType::TIERCE,
        core::ChordClassType c = core::ChordClassType::TETRAD);

    // Setter pour l'intervalle d'harmonisation
    void set_harm(HarmoIntervalType harm_intvl) {
        _harm_intvl = harm_intvl;
    }

    // Setter pour la classe d'accord
    void set_chord(core::ChordClassType chord_class) {
        _chord_class = chord_class;
    }

    /*
     * Construire une harmonisation (liste d'accords) 
     * à partir d'une gamme et d'une note tonique.
     * Par exemple, harmoniser une gamme majeure en accords triades.
     *
     * @param gamme : la gamme utilisée pour l'harmonisation
     * @param interval : harmonisation en tierce en quarte ??...
     * @return : vecteur de d'accords.
     */
    std::vector<core::Chord> 
    harmonize(const musical::core::scale::ScaleKeyed&);



};
} 

