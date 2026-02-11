#include <musical/ScoreElements/KeySignature.h>
#include <musical/Core/note/Note.h>
//#include <musical/Core/note/NoteService.h>
#include <musical/Core/scale/ScaleKeyedFactory.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <sstream>


using namespace musical;

#include <musical/ScoreElements/KeySignature.h>

using namespace musical;

KeyModeType KeySignature::mode_from_string(const std::string& name_input)
{
    static const std::unordered_map<std::string, KeyModeType> mode_map = {
        {"ionian",       KeyModeType::IONIAN},
        {"dorian",       KeyModeType::DORIAN},
        {"phrygian",     KeyModeType::PHRYGIAN},
        {"lydian",       KeyModeType::LYDIAN},
        {"mixolydian",   KeyModeType::MIXOLYDIAN},
        {"aeolian",      KeyModeType::AEOLIAN},
        {"locrian",      KeyModeType::LOCRIAN}
    };

    std::string name = name_input;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    // std::cout << "[KeySignature::" << __func__ << "]"
    //     << "\n  >>Var: name =" << name
    //     << std::endl;    

    auto it = mode_map.find(name);
    if (it != mode_map.end()) {
        return it->second;
    }

    throw std::invalid_argument("[KeySignature::mode_from_string]: invalid mode string '" + name + "'");
}

std::string KeySignature::to_french(KeyModeType m)
{
    switch(m) {

        case KeyModeType::IONIAN:      return "ionien";
        case KeyModeType::AEOLIAN:     return "éolien";            
        case KeyModeType::DORIAN:      return "dorien";
        case KeyModeType::PHRYGIAN:    return "phrygien";
        case KeyModeType::LYDIAN:      return "lydien";
        case KeyModeType::MIXOLYDIAN:  return "mixolydien";
        case KeyModeType::LOCRIAN:     return "locrien";
            
        default: 
            throw std::invalid_argument("[KeySignature::to_french] nunknown mode");
    }
}
std::string KeySignature::to_string(KeyModeType m)
{
    switch(m) {

        case KeyModeType::IONIAN:      return "ionian";
        case KeyModeType::AEOLIAN:     return "aeolian";            
        case KeyModeType::DORIAN:      return "dorian";
        case KeyModeType::PHRYGIAN:    return "phrygian";
        case KeyModeType::LYDIAN:      return "lydian";
        case KeyModeType::MIXOLYDIAN:  return "mixolydian";
        case KeyModeType::LOCRIAN:     return "locrian";
        	
        default: 
            throw std::invalid_argument("KeySignature::to_string(..)\nunknown mode");
    }
}
std::array<std::string,SHARP_KEY_COUNT> KeySignature::circle_fifths(const Note& note)
{
    std::array<std::string,SHARP_KEY_COUNT> result{};

    ScaleKeyed gamme = ScaleKeyedFactory::create(IntervalType::QUINTE_JUSTE,note);

    gamme.truncate(SHARP_KEY_COUNT); 

    for (std::size_t i = 0; i < SHARP_KEY_COUNT; ++i) {
        result[i] = musical::musical::io::note::formatter::to_string(gamme[i+1]);  //gamme[i+1] i+1 pour de pas renvoyer la première tonalité.
    }
    return result;
}
std::array<std::string,FLAT_KEY_COUNT> KeySignature::circle_fourths(const Note&note)    
{
    std::array<std::string,FLAT_KEY_COUNT> result{};

    ScaleKeyed gamme = ScaleKeyedFactory::create(IntervalType::QUARTE_JUSTE,note,false);

    gamme.truncate(FLAT_KEY_COUNT); 

    for (std::size_t i = 0; i < FLAT_KEY_COUNT; ++i) {
        result[i] = musical::musical::io::note::formatter::to_string(gamme[i]);  
    }
    return result;
}

//STATIC
std::string KeySignature::from_mei(
    const std::string& mei_mode, 
    const std::string& mei_keysig)
{
    // Transformation du mode MEI en enum
    KeyModeType mode = mode_from_string(mei_mode);

    switch(mode)
    {
    case KeyModeType::IONIAN:
        {
            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "c"},   {"1s", "g"},  {"2s", "d"},  {"3s", "a"},
                {"4s", "e"},   {"5s", "b"},  {"6s", "f#"}, {"7s", "c#"},
                {"1f", "f"},   {"2f", "bb"}, {"3f", "eb"}, {"4f", "ab"},
                {"5f", "db"},  {"6f", "gb"}, {"7f", "cb"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) {
                return it->second;
            }
        }
        break;

    case KeyModeType::AEOLIAN:
        {
            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "a"},   {"1s", "e"},  {"2s", "b"},  {"3s", "f#"},
                {"4s", "c#"},  {"5s", "g#"}, {"6s", "d#"}, {"7s", "a#"},
                {"1f", "d"},   {"2f", "g"},  {"3f", "c"},  {"4f", "f"},
                {"5f", "bb"},  {"6f", "eb"}, {"7f", "ab"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) {
                return it->second;
            }
        }
        break;
    case KeyModeType::DORIAN:
        {

            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "d"},   {"1s", "a"},  {"2s", "e"},  {"3s", "b"},
                {"4s", "f#"},  {"5s", "c#"}, {"6s", "g#"}, {"7s", "d#"},
                {"1f", "g"},   {"2f", "c"},  {"3f", "f"},  {"4f", "bb"},
                {"5f", "eb"},  {"6f", "ab"}, {"7f", "db"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) return it->second;

        }
        break;
    case KeyModeType::PHRYGIAN:
        {

            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "e"},   {"1s", "b"},  {"2s", "f#"}, {"3s", "c#"},
                {"4s", "g#"},  {"5s", "d#"}, {"6s", "a#"}, {"7s", "e#"},
                {"1f", "a"},   {"2f", "d"},  {"3f", "g"},  {"4f", "c"},
                {"5f", "f"},   {"6f", "bb"}, {"7f", "eb"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) return it->second;

        }
        break;
    case KeyModeType::LYDIAN:
        {

            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "f"},   {"1s", "c"},  {"2s", "g"},  {"3s", "d"},
                {"4s", "a"},   {"5s", "e"},  {"6s", "b"},  {"7s", "f#"},
                {"1f", "bb"},  {"2f", "eb"}, {"3f", "ab"}, {"4f", "db"},
                {"5f", "gb"},  {"6f", "cb"}, {"7f", "fb"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) return it->second;

        }
        break;
    case KeyModeType::MIXOLYDIAN:
        {

            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "g"},   {"1s", "d"},  {"2s", "a"},  {"3s", "e"},
                {"4s", "b"},   {"5s", "f#"}, {"6s", "c#"}, {"7s", "g#"},
                {"1f", "c"},   {"2f", "f"},  {"3f", "bb"}, {"4f", "eb"},
                {"5f", "ab"},  {"6f", "db"}, {"7f", "gb"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) return it->second;

        }
        break;
    case KeyModeType::LOCRIAN:
        {
            static const std::map<std::string, std::string> MEI_TO_KEY = {
                {"0",  "b"},   {"1s", "f#"}, {"2s", "c#"}, {"3s", "g#"},
                {"4s", "d#"},  {"5s", "a#"}, {"6s", "e#"}, {"7s", "b#"},
                {"1f", "e"},   {"2f", "a"},  {"3f", "d"},  {"4f", "g"},
                {"5f", "c"},   {"6f", "f"},  {"7f", "bb"}
            };

            auto it = MEI_TO_KEY.find(mei_keysig);
            if (it != MEI_TO_KEY.end()) return it->second;

            
        }
        break;
    default:
        break;
    }

    std::ostringstream err;
    err << "🔥 ERROR in [KeySignature::" << __func__ << "]"
        << "\n  >> mei_keysig=" << mei_keysig
        << "\n  >> mode=" << mei_mode << std::endl;
    std::cerr << err.str();
    throw std::runtime_error(err.str());
}


std::string KeySignature::to_mei_string(
    KeyModeType mode, 
    const Note& tonality)
{
    /*std::cout << "[KeySignature::"<<__func__ <<"]"
        << "\n  >>Var: mode: " << KeySignature::to_string(mode)
        << "\n  >>Var: tonality: " << tonality.to_string()        
        << std::endl;*/

    std::string n = musical::musical::io::note::formatter::to_string(tonality);//= NoteService::normalize(note_input); 

    switch(mode)
    {
    case KeyModeType::IONIAN:
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"c",  "0"},   {"g",  "1s"},  {"d",  "2s"},  {"a",  "3s"},
                {"e",  "4s"},  {"b",  "5s"},  {"f#", "6s"},  {"c#", "7s"},
                {"f",  "1f"},  {"bb", "2f"},  {"eb", "3f"},  {"ab", "4f"},
                {"db", "5f"},  {"gb", "6f"},  {"cb", "7f"}
            };


            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second; 
            }
        }
        break;
    case KeyModeType::AEOLIAN:
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"a",  "0"},   {"e",  "1s"},  {"b",  "2s"},  {"f#", "3s"},
                {"c#", "4s"},  {"g#", "5s"},  {"d#", "6s"},  {"a#", "7s"},
                {"d",  "1f"},  {"g",  "2f"},  {"c",  "3f"},  {"f",  "4f"},
                {"bb", "5f"},  {"eb", "6f"},  {"ab", "7f"}
            };
            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second; 
            }
        }
        break;        
    case KeyModeType::DORIAN:
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"d",  "0"},   {"a",  "1s"},  {"e",  "2s"},  {"b",  "3s"},
                {"f#", "4s"},  {"c#", "5s"},  {"g#", "6s"},  {"d#", "7s"},
                {"g",  "1f"},  {"c",  "2f"},  {"f",  "3f"},  {"bb", "4f"},
                {"eb", "5f"},  {"ab", "6f"},  {"db", "7f"}
            };
            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second;
            }
        }        
        break;
    case KeyModeType::PHRYGIAN:
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"e",  "0"},   {"b",  "1s"},  {"f#", "2s"},  {"c#", "3s"},
                {"g#", "4s"},  {"d#", "5s"},  {"a#", "6s"},  {"e#", "7s"},
                {"a",  "1f"},  {"d",  "2f"},  {"g",  "3f"},  {"c",  "4f"},
                {"f",  "5f"},  {"bb", "6f"},  {"eb", "7f"}
            };
            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second;
            }
        }        
        break;
    case KeyModeType::LYDIAN:
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"f",  "0"},   {"c",  "1s"},  {"g",  "2s"},  {"d",  "3s"},
                {"a",  "4s"},  {"e",  "5s"},  {"b",  "6s"},  {"f#", "7s"},
                {"bb", "1f"},  {"eb", "2f"},  {"ab", "3f"},  {"db", "4f"},
                {"gb", "5f"},  {"cb", "6f"},  {"fb", "7f"}
            };
            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second;
            }
        }        
        break;
    case KeyModeType::MIXOLYDIAN:
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"g",  "0"},   {"d",  "1s"},  {"a",  "2s"},  {"e",  "3s"},
                {"b",  "4s"},  {"f#", "5s"},  {"c#", "6s"},  {"g#", "7s"},
                {"c",  "1f"},  {"f",  "2f"},  {"bb", "3f"},  {"eb", "4f"},
                {"ab", "5f"},  {"db", "6f"},  {"gb", "7f"}
            };
            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second;
            }
        }        
        break;
    case KeyModeType::LOCRIAN:    
        {
            static const std::map<std::string, std::string> KEY_TO_MEI = {
                {"b",  "0"},   {"f#", "1s"},  {"c#", "2s"},  {"g#", "3s"},
                {"d#", "4s"},  {"a#", "5s"},  {"e#", "6s"},  {"b#", "7s"},
                {"e",  "1f"},  {"a",  "2f"},  {"d",  "3f"},  {"g",  "4f"},
                {"c",  "5f"},  {"f",  "6f"},  {"bb", "7f"}
            };
            auto it = KEY_TO_MEI.find(n);
            if (it != KEY_TO_MEI.end()){
                return it->second;
            }
        }                 
        break;
    default:
        break;
    }

    std::ostringstream oss;
    oss << "[KeySignature::" << __func__ << "]"
        << "\n  failure" 
        << std::endl;

    throw std::runtime_error(oss.str());

}