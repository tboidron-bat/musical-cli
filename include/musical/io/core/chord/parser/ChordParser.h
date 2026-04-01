#pragma once

#include <musical/core/chord/Chord.h>
#include <musical/io/core/chord/parser/ChordLexer.h> //token_t

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