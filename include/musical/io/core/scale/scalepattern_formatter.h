#pragma once

#include <string>

#include <musical/core/scale/scale_defs.h>

namespace musical::io::scale::scalepattern_formatter {

    std::string 
    to_string(const musical::core::scale::ScalePatternType);

    std::string 
    to_french(musical::core::scale::ScalePatternType);    
    
}