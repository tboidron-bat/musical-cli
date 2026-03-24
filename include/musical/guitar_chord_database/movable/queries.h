#pragma once

#include <vector>
#include <utility>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database::queries::movable
{

using IntervalMask = uint64_t;

// ============================================================
// FIND SHAPES BY MASK
// ============================================================
std::vector<Diagram>
find_diagrams(IntervalMask mask);

// ============================================================
// FIND SHAPES BY MASK + CAGED
// ============================================================
std::vector<Diagram>
find_diagrams(
    IntervalMask mask,
    Diagram::CAGED shape);

// ============================================================
// FIND ALL SHAPES
// ============================================================
std::vector<Diagram>
find_all_diagrams();

std::vector<Diagram>
find_all_diagrams(Diagram::CAGED shape);

// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<IntervalMask, Diagram>
get_random_diagram();

} // namespace chord::database::queries::movable