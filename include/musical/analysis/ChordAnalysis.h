#pragma once

namespace musical::core::chord {
    class Chord;
}

namespace musical::analysis::chord
{
    bool is_minor(const musical::core::chord::Chord& chord);
    bool is_major(const musical::core::chord::Chord& chord);
    bool has_seventh(const musical::core::chord::Chord& chord);
}