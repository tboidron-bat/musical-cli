#pragma once

#include <vector>
#include <string>
#include <utility>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database::queries::movable
{

// ============================================================
// FIND SHAPES BY TYPE
// ============================================================
std::vector<Diagram>
find_diagrams(const std::string& chord_type_name);

// ============================================================
// FIND SHAPES BY TYPE + CAGED
// ============================================================
std::vector<Diagram>
find_diagrams(
    const std::string& chord_type_name,
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

std::pair<std::string, Diagram>
get_random_diagram();


}