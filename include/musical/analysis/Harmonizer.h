#pragma once

#include <musical/core/chord/Chord.h>
#include <musical/core/chord/ChordType.h>
#include <musical/core/scale/ScaleKeyed.h>
#include <musical/core/chord/Factory.h>

#include <vector>
#include <cstdint>

namespace musical::analysis {

enum class HarmoIntervalType : uint8_t {    

    TIERCE,
    QUARTE,
    QUINTE,
    SIXTE
};    

enum class ChordClassType {
    DYAD=2,     
    TRIAD,    
    TETRAD,   
    PENTAD,   
    HEXAD,    
    UNKNOWN
};  
// ChordClassType ChordType::class_type() const
// {
//     // +1 car la tonique n'est pas stockée dans _intervals
//     switch (size() + 1)
//     {
//         case 2: return ChordClassType::DYAD;
//         case 3: return ChordClassType::TRIAD;
//         case 4: return ChordClassType::TETRAD;
//         case 5: return ChordClassType::PENTAD;
//         case 6: return ChordClassType::HEXAD;
//         default: return ChordClassType::UNKNOWN;
//     }
// } 


class Harmonizer {

    HarmoIntervalType _harm_intvl;
    ChordClassType _chord_class;

public:
    Harmonizer(
        HarmoIntervalType h = HarmoIntervalType::TIERCE,
        ChordClassType c = ChordClassType::TETRAD);

    // Setter pour l'intervalle d'harmonisation
    void set_harm(HarmoIntervalType harm_intvl) {
        _harm_intvl = harm_intvl;
    }

    // Setter pour la classe d'accord
    void set_chord(ChordClassType chord_class) {
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
    std::vector<core::chord::Chord> 
    harmonize(const musical::core::scale::ScaleKeyed&);



};
} 

