#pragma once

#include <cstdint>

namespace musical {

    enum class IntervalType : uint8_t {

        TONIQUE = 0,
        SECONDE_MINEURE = 1,
        SECONDE_MAJEURE = 2,
        TIERCE_MINEURE = 3,
        TIERCE_MAJEURE = 4,
        QUARTE_JUSTE = 5,
        TRITON = 6,
        QUINTE_JUSTE = 7,
        SIXTE_MINEURE = 8,
        SIXTE_MAJEURE = 9,
        SEPTIEME_MINEURE = 10,
        SEPTIEME_MAJEURE = 11,
        OCTAVE = 12,
        
        // Au-delà de l'octave (douzième, treizième, etc.)
        NEUVIEME_MINEURE = 13,  // octave + seconde mineure
        NEUVIEME_MAJEURE = 14,  // octave + seconde majeure
        DIXIEME_MINEURE = 15,   // octave + tierce mineure
        DIXIEME_MAJEURE = 16,   // octave + tierce majeure
        ONZIEME = 17,           // octave + quarte juste
        ONZIEME_AUGMENTEE = 18, // octave + triton
        DOUZIEME = 19,          // octave + quinte juste
        TREIZIEME_MINEURE = 20, // octave + sixte mineure
        TREIZIEME_MAJEURE = 21, // octave + sixte majeure
        QUATORZIEME_MINEURE = 22, // octave + septième mineure
        QUATORZIEME_MAJEURE = 23, // octave + septième majeure
        DOUBLE_OCTAVE = 24       // 2 octaves
    };


    enum class ChordClassType {
        DYAD=2,     // 2 notes
        TRIAD,    // 3 notes (ex: majeur, mineur, diminué)
        TETRAD,   // 4 notes (ex: accords 7e)
        PENTAD,   // 5 notes (ex: accords 9e)
        HEXAD,    // 6 notes (ex: accords 11e)
        UNKNOWN
    };    

    enum class CommonChordType {

        // --- Triades basiques --- 
        MAJOR,       
        MINOR,       
        DIMINISHED,  
        AUGMENTED,   

        // Accords avec septième
        MAJOR7,            // Majeur 7
        DOMINANT7,         // Septième de dominante
        MINOR7,            // Mineur 7
        HALF_DIMINISHED7,  // Demi-diminué (m7♭5)
        DIMINISHED7,       // Diminué 7

        // Accords avec extensions
        MAJOR9,            // Majeur 9
        DOMINANT9,         // 9 dominante
        MINOR9,            // Mineur 9

        MAJOR11,           // Majeur 11
        DOMINANT11,        // 11 dominante
        MINOR11,           // Mineur 11

        MAJOR13,           // Majeur 13
        DOMINANT13,        // 13 dominante
        MINOR13,           // Mineur 13

        // Accords altérés
        DOMINANT7_FLAT5,   // 7b5
        DOMINANT7_SHARP5,  // 7#5
        DOMINANT7_FLAT9,   // 7b9
        DOMINANT7_SHARP9,  // 7#9

        // Autres accords
        SUSPENDED2,        // Sus2
        SUSPENDED4,        // Sus4
        ADD9,              // add9
        MAJOR6,            // 6 majeur
        MINOR6,            // 6 mineur

        // Accord vide ou inconnu
        NOCHORD, //N.C
        UNKNOWN
    };  



    //enum class FigureType { WHOLE, HALF, QUARTER, EIGHTH, SIXTEENTH /* etc. */ };

    //enum class Mode { IONIAN, DORIAN, PHRYGIAN, LYDIAN, MIXOLYDIAN, AEOLIAN, LOCRIAN };

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


