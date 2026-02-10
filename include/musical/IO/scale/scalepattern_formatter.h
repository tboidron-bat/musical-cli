#pragma once

#include <string>

#include <musical/Core/MusicalCoreEnums.h>

namespace musical::scalepattern_formatter {

    std::string to_string(const ScalePatternType);
    std::string to_french(ScalePatternType);    
    
}