#pragma once

#include <vector>
#include <utility>
#include <optional>

#include <musical/chord_db/Diagram.h>
#include <musical/core/Tone.h>
#include <musical/core/chord/ChordType.h>
#include <musical/chord_db/open/database.h> // key_t

namespace chord::db::queries::open
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
// FIND ALL OPEN DIAGRAMS
// ============================================================   
std::vector<std::pair<IntervalMask, Diagram>> 
find_all_diagrams(std::optional<Diagram::CAGED> shape = std::nullopt);
// ============================================================
// RANDOM (TYPE SAFE)
// ============================================================
Diagram get_random();

//TODO REFACTOR: std::pair<Tone, Diagram> ?
// std::pair<key_t, Diagram>
// get_random();
} // namespace chord::db::queries::open