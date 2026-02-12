#pragma once

#include <vector>
#include <string>
#include <map>
#include <cstdint>

#include <musical/Core/scale/ScalePattern.h>

namespace musical::core::scale {

class ScalePatternFactory 
{
public:
    static ScalePattern create(ScalePatternType type);
    static ScalePattern create(const std::string& name);

    // --- Retourne la liste de tous les types de gammes connus ---
    static std::vector<ScalePatternType> list_types();        
private:
    // --- Definis les intervalles de toutes les gammes connus  ---
    static const std::map<ScalePatternType, std::vector<int8_t>> s_scales;        
};
}