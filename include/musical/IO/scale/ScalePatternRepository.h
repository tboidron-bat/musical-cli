#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstdint>

#include <musical/Core/MusicalCoreEnums.h>

namespace musical {

class ScaleRepository {
    
public:
    /// Charge les gammes utilisateur depuis un fichier texte
    //# ~/.config/musical/scale.conf
    //my_scale = 0 1 4 7 10
    //enigmatic = 0 1 4 6 8 11
    //brancher mscale --add


    void loadFromFile(const std::string& path);
    void loadFromXmlFile(const std::string& xml_file_path);
};

}
