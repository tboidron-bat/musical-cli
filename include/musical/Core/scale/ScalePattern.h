#pragma once

/**
 * @brief 
 *Représente une échelle musicale sous forme d'une suite d'intervalles et d'un nom.
 */

#include <vector>
#include <cstdint>
#include <musical/Core/MusicalCoreEnums.h>

namespace musical {


class ScalePattern {

private:

    ScalePatternType _type;
    std::vector<int8_t> _intervals;

public:

    // ---  Constructors ---
    ScalePattern(ScalePatternType,std::vector<int8_t>);

    //  ---  Accessors ---
    ScalePatternType get_type() const { return _type;   }
    const std::vector<int8_t>& get_intervals() const { return _intervals; }
};

}