#pragma once

#include <ostream>

namespace musical::core::chord {
    class ChordType;
}
namespace musical::io::chord {

    std::string to_string(const musical::core::chord::ChordType& chord_type);
        
} // namespace musical::io::chord
