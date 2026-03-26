#pragma once

#include <vector>
#include <utility>

#include <musical/guitar_chord_database/Diagram.h>
#include <musical/guitar_chord_database/open/database.h> // NoteEnum, IntervalMask, key_t

namespace chord::database::queries::open
{

// ============================================================
// CORE API (TYPE SAFE)
// ============================================================

// ------------------------------------------------------------
// FIND POSITIONS (root + mask)
// ------------------------------------------------------------
std::vector<Diagram>
find_positions(
    NoteEnum root,
    IntervalMask mask
);

// ------------------------------------------------------------
// FIND POSITIONS (root + mask + shape)
// ------------------------------------------------------------
std::vector<Diagram>
find_positions(
    NoteEnum root,
    IntervalMask mask,
    Diagram::CAGED shape
);

// ------------------------------------------------------------
// FIND ALL POSITIONS (mask only)
// ------------------------------------------------------------
std::vector<Diagram>
find_all_positions(
    IntervalMask mask
);

// ------------------------------------------------------------
// FIND ALL DIAGRAMS
// ------------------------------------------------------------
std::vector<Diagram>
find_all_diagrams();


// ============================================================
// RANDOM (TYPE SAFE)
// ============================================================

// ------------------------------------------------------------
// RANDOM CHORD
// ------------------------------------------------------------
std::pair<key_t, Diagram>
get_random();

} // namespace chord::database::queries::open