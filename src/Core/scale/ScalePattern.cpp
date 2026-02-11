#include <musical/Core/scale/ScalePattern.h>

namespace musical {

ScalePattern::ScalePattern(ScalePatternType type, std::vector<int8_t> intervals)
    : _type(type), _intervals(std::move(intervals))
{}

}
// std::string ScalePattern::to_string() const {
//     std::ostringstream oss;
//     oss << scale_formatter::to_string(_name) << " : ";

//     for (size_t i = 0; i < _degres.size(); ++i) {
//         oss << _degres[i];
//         if (i != _degres.size() - 1)
//             oss << " ";
//     }

//     return oss.str();
// }