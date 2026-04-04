#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <optional>

#include <musical/chord_db/Diagram.h>

namespace chord::db::queries::movable
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

} // namespace chord::db::queries::movable