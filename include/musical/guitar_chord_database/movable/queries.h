#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <optional>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database::queries::movable
{

using IntervalMask = uint64_t;

// ============================================================
std::vector<Diagram>
find_diagrams(
    IntervalMask mask,
    std::optional<Diagram::CAGED> shape = std::nullopt);
// ============================================================    
std::vector<Diagram>
find_all_diagrams(std::optional<Diagram::CAGED> shape = std::nullopt);
// ============================================================
// RANDOM DIAGRAM
// ============================================================
std::pair<IntervalMask, Diagram>
get_random_diagram();

} // namespace chord::database::queries::movable