#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstdint> 
#include <map> 
#include <algorithm> 

#include <musical/Core/note/Note.h>
#include <musical/common/musical_constants.h>

namespace musical::score {

    constexpr std::size_t SHARP_KEY_COUNT = musical::core::DIATONIC_NOTE_COUNT;    
    constexpr std::size_t FLAT_KEY_COUNT = musical::core::DIATONIC_NOTE_COUNT;        

enum class KeyModeType { 
    IONIAN, 
    AEOLIAN,    
    DORIAN,
    PHRYGIAN,
    LYDIAN,
    MIXOLYDIAN,
    LOCRIAN 
};   
class KeySignature
{
public:  

    static std::vector<KeyModeType> all_modes() {
        return {
            KeyModeType::IONIAN,
            KeyModeType::AEOLIAN,            
            KeyModeType::DORIAN,
            KeyModeType::PHRYGIAN,
            KeyModeType::LYDIAN,
            KeyModeType::MIXOLYDIAN,
            KeyModeType::LOCRIAN
        };
    }

    static KeyModeType mode_from_string(const std::string&name);
    /*
    Renvoie la chaine de caratère 
    pour le fichier MEI.
    */
    static std::string to_mei_string(KeyModeType,const core::Note&);    

    static std::string from_mei(const std::string&,const std::string&);        
    /* 
        Renvoie une chaine de caratère à partir du Mode.
    */
    static std::string to_string(KeyModeType); 
    static std::string to_french(KeyModeType);    

    static std::array<std::string,SHARP_KEY_COUNT> circle_fifths(const core::Note&);

    static std::array<std::string,FLAT_KEY_COUNT> circle_fourths(const core::Note&);    
};

}



