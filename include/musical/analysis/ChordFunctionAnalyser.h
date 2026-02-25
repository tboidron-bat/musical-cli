#pragma once

#include <string>

namespace musical::core::chord {
    class Chord;
}

namespace musical::core::scale {
    class ScaleKeyed;
}

namespace musical::analysis
{

class ChordFunctionAnalyser
{
public:
    static std::string to_string(
        const musical::core::chord::Chord& chord,
        const musical::core::scale::ScaleKeyed& gamme
    );
};

} // namespace musical::analysis