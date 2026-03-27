#pragma once

#include <musical/Core/chord/Chord.h>
#include <musical/io/chord/in/ChordLexer.h> //token_t

#include <vector>
#include <optional>

namespace musical::io::chord {

class ChordParser
{
public:
    static std::optional<core::chord::Chord>
    parse(const std::vector<token_t>& tokens);
};

} // namespace musical::io::chord