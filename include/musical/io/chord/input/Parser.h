#pragma once

#include <musical/Core/chord/Chord.h>
#include <musical/io/chord/input/tokens.h>

#include <vector>
#include <optional>

namespace musical::io::chord {

class Parser
{
public:
    static std::optional<core::chord::Chord>
    parse(const std::vector<Token>& tokens);
};

} // namespace musical::io::chord