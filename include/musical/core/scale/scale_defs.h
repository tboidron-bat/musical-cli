#pragma once

#include <cstdint>

namespace musical::core::scale {


    enum class ScalePatternType {
        // Gammes de base
        CHROMATIC, MAJOR, MINOR, IONIAN, AEOLIAN,
        // Modes diatoniques
        DORIAN, PHRYGIAN, LYDIAN, MIXOLYDIAN, LOCRIAN,
        // Mineure harmonique et ses modes
        HARMONIC_MINOR,LOCRIAN_NATURAL_6,IONIAN_AUGMENTED,DORIAN_SHARP_4,PHRYGIAN_DOMINANT,
        LYDIAN_SHARP_2,ULTRAPHRYGIAN,SUPERLOCRIAN_DIMINISHED,
        // Gammes mélodiques mineures (Jazz Minor)
        JAZZ_MINOR,DORIAN_FLAT2,LYDIAN_AUGMENTED,LYDIAN_DOMINANT,
        MIXOLYDIAN_FLAT6,AEOLIAN_FLAT5,SUPERLOCRIAN,
        // Pentatoniques
        PENTATONIC_MAJOR,PENTATONIC_MINOR,BLUES,
        // Gammes exotiques
        HUNGARIAN_MAJOR,HUNGARIAN_MINOR,EGYPTIAN,ARABIC,KLEZMER,
        HIRAJOSHI,CHINESE,
        // Valeur par défaut (sécurité)
        //UNKNOWN,
        __COUNT
    };    

    // Ajoute ici d’autres enums métier nécessaires...    
}


