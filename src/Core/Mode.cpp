#include <musical/Core/Mode.h>
#include <musical/Core/scalepattern_formatter.h>

#include <iostream>

namespace musical {

// --- Constructeurs ----------------------------------------------------------

Mode::Mode(ModeType m)
: 
ScalePattern(to_scale_type(m)), _mode(m) {}

Mode::Mode(const std::string& name)
: 
ScalePattern(
    ScalePattern::from_string(name)), 
    _mode(from_string(name)
    ) 
{
    // std::cout << "[Mode::" << __func__ << "]"
    //     << "\n  >>Var: name =" << name
    //     << std::endl;
}

// --- Méthodes publiques -----------------------------------------------------

// std::string Mode::to_string() const 
// {ScalePattern
//     const ScalePatternType type = Mode::to_scale_type(_mode);
//     return musical::scale_formatter::to_string(type);
// }

// std::string Mode::to_french() const 
// {
//     ScalePatternType type = Mode::to_scale_type(_mode);    
//     return musical::scale_formatter::to_french(type);
// }

// --- Statics ---------------------------------------------------------------

ScalePatternType Mode::to_scale_type(ModeType m) {
    switch(m) {
        case ModeType::IONIAN:     return ScalePatternType::IONIAN;
        case ModeType::DORIAN:     return ScalePatternType::DORIAN;
        case ModeType::PHRYGIAN:   return ScalePatternType::PHRYGIAN;
        case ModeType::LYDIAN:     return ScalePatternType::LYDIAN;
        case ModeType::MIXOLYDIAN: return ScalePatternType::MIXOLYDIAN;
        case ModeType::AEOLIAN:    return ScalePatternType::AEOLIAN;
        case ModeType::LOCRIAN:    return ScalePatternType::LOCRIAN;
        default:                   return ScalePatternType::UNKNOWN;
    }
}

Mode::ModeType Mode::from_string(const std::string& s) {

    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "ionian")     return ModeType::IONIAN;
    if (lower == "dorian")     return ModeType::DORIAN;
    if (lower == "phrygian")   return ModeType::PHRYGIAN;
    if (lower == "lydian")     return ModeType::LYDIAN;
    if (lower == "mixolydian") return ModeType::MIXOLYDIAN;
    if (lower == "aeolian")    return ModeType::AEOLIAN;
    if (lower == "locrian")    return ModeType::LOCRIAN;
    return ModeType::UNKNOWN;
}

} // namespace musical
