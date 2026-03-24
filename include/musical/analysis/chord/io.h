#pragma once

#include <ostream>

namespace musical::core::chord {
    class ChordType;
}

namespace musical::analysis::chord {

    std::ostream& operator<<(
        std::ostream& os, 
        const musical::core::chord::ChordType& chod_type);
        
} // namespace musical::analysis::chord
