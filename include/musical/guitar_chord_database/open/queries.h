#pragma once

#include <vector>
#include <utility>
#include <optional>

#include <musical/guitar_chord_database/Diagram.h>
#include <musical/core/Tone.h>
#include <musical/core/chord/ChordType.h>
#include <musical/guitar_chord_database/open/database.h> // key_t

namespace chord::database::queries::open
{
    using IntervalMask = musical::core::chord::ChordType::IntervalMask;

    using musical::core::Tone;

// ============================================================
std::vector<Diagram>
find_diagrams(
    Tone root,
    IntervalMask mask,
    std::optional<Diagram::CAGED> shape = std::nullopt);
// ============================================================
std::vector<Diagram>
find_all_diagrams(std::optional<IntervalMask> mask = std::nullopt);
// ============================================================
// RANDOM (TYPE SAFE)
// ============================================================
Diagram get_random();

//TODO REFACTOR: std::pair<Tone, Diagram> ?
// std::pair<key_t, Diagram>
// get_random();
} // namespace chord::database::queries::open