#include <musical/IO/scale/scalepattern_formatter.h>

#include <cassert>

using namespace musical;

std::string scalepattern_formatter::to_string(ScalePatternType N) {

    switch(N) {

        case ScalePatternType::CHROMATIC: return "CHROMATIC";
        case ScalePatternType::MAJOR: return "MAJOR";
        case ScalePatternType::IONIAN: return "IONIAN";            
        case ScalePatternType::MINOR: return "MINOR";
        case ScalePatternType::AEOLIAN: return "AEOLIAN";            
        case ScalePatternType::DORIAN: return "DORIAN";
        case ScalePatternType::PHRYGIAN: return "PHRYGIAN";
        case ScalePatternType::LYDIAN: return "LYDIAN";
        case ScalePatternType::MIXOLYDIAN: return "MIXOLYDIAN";
        case ScalePatternType::LOCRIAN: return "LOCRIAN";
        case ScalePatternType::HARMONIC_MINOR: return "HARMONIC_MINOR";
        case ScalePatternType::LOCRIAN_NATURAL_6: return "LOCRIAN_NATURAL_6";
        case ScalePatternType::IONIAN_AUGMENTED: return "IONIAN_AUGMENTED";
        case ScalePatternType::DORIAN_SHARP_4: return "DORIAN_SHARP_4";
        case ScalePatternType::PHRYGIAN_DOMINANT: return "PHRYGIAN_DOMINANT";
        case ScalePatternType::LYDIAN_SHARP_2: return "LYDIAN_SHARP_2";
        case ScalePatternType::ULTRAPHRYGIAN: 
            return "ULTRAPHRYGIAN";
        case ScalePatternType::SUPERLOCRIAN_DIMINISHED: 
            return "SUPERLOCRIAN_DIMINISHED";
        case ScalePatternType::JAZZ_MINOR: 
            return "JAZZ_MINOR";
        case ScalePatternType::DORIAN_FLAT2: return "DORIAN_FLAT2";
        case ScalePatternType::LYDIAN_AUGMENTED: return "LYDIAN_AUGMENTED";
        case ScalePatternType::LYDIAN_DOMINANT: return "LYDIAN_DOMINANT";
        case ScalePatternType::MIXOLYDIAN_FLAT6: return "MIXOLYDIAN_FLAT6";
        case ScalePatternType::AEOLIAN_FLAT5: return "AEOLIAN_FLAT5";
        case ScalePatternType::SUPERLOCRIAN: return "SUPERLOCRIAN";
        case ScalePatternType::PENTATONIC_MAJOR: return "PENTATONIC_MAJOR";
        case ScalePatternType::PENTATONIC_MINOR: return "PENTATONIC_MINOR";
        case ScalePatternType::BLUES: return "BLUES";
        case ScalePatternType::HUNGARIAN_MAJOR: return "HUNGARIAN_MAJOR";
        case ScalePatternType::HUNGARIAN_MINOR: return "HUNGARIAN_MINOR";
        case ScalePatternType::EGYPTIAN: return "EGYPTIAN";
        case ScalePatternType::ARABIC: return "ARABIC";
        case ScalePatternType::KLEZMER: return "KLEZMER";
        case ScalePatternType::HIRAJOSHI: return "HIRAJOSHI";
        case ScalePatternType::CHINESE: return "CHINESE";
        case ScalePatternType::__COUNT:
            return "INVALID_SCALE_PATTERN";
    }
    assert(false && "Unhandled ScalePatternType");
    return "UNKNOWN"; // sécurité si aucun match (ex: enum corrompu)
}

std::string scalepattern_formatter::to_french(ScalePatternType type) {
    switch(type) {
        case ScalePatternType::CHROMATIC: return "Chromatique";        
        case ScalePatternType::MAJOR: return "Majeure";
        case ScalePatternType::IONIAN: return "Ionien";            
        case ScalePatternType::MINOR: return "Mineure";
        case ScalePatternType::AEOLIAN: return "Éolien";
        case ScalePatternType::DORIAN: return "Dorien";
        case ScalePatternType::PHRYGIAN: return "Phrygien";
        case ScalePatternType::LYDIAN: return "Lydien";
        case ScalePatternType::MIXOLYDIAN: return "Mixolydien";
        case ScalePatternType::LOCRIAN: return "Locrien";
        case ScalePatternType::HARMONIC_MINOR: return "Mineure harmonique";
        case ScalePatternType::JAZZ_MINOR: return "Mineure mélodique";
        case ScalePatternType::BLUES: return "Blues";
        case ScalePatternType::PENTATONIC_MAJOR: return "Pentatonique majeure";
        case ScalePatternType::PENTATONIC_MINOR: return "Pentatonique mineure";
        case ScalePatternType::HUNGARIAN_MAJOR: return "Hongroise majeure";
        case ScalePatternType::HUNGARIAN_MINOR: return "Hongroise mineure";
        case ScalePatternType::EGYPTIAN: return "Égyptienne";
        case ScalePatternType::ARABIC: return "Arabe";
        case ScalePatternType::KLEZMER: return "Klezmer";
        case ScalePatternType::HIRAJOSHI: return "Hirajoshi";
        case ScalePatternType::CHINESE: return "Chinoise";
        default:
            assert(false && "Unhandled ScalePatternType in to_french");
            return "Inconnue";
    }
}

