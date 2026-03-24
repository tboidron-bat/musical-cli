#include <musical/guitar_chord_database/movable/database.h>

// modules
#include <musical/guitar_chord_database/movable/maj.h>
#include <musical/guitar_chord_database/movable/min.h>
#include <musical/guitar_chord_database/movable/aug.h>
#include <musical/guitar_chord_database/movable/dim.h>
#include <musical/guitar_chord_database/movable/sus2.h>
#include <musical/guitar_chord_database/movable/sus4.h>

namespace chord::database
{

// ------------------------------------------------------------
// Merge util (local au cpp)
// ------------------------------------------------------------
static void merge_into(
    movable_diagram_map& dst,
    const movable_diagram_map& src)
{
    for (const auto& [mask, diagrams] : src)
    {
        auto& vec = dst[mask];
        vec.insert(vec.end(), diagrams.begin(), diagrams.end());
    }
}

// ------------------------------------------------------------
// Global DB
// ------------------------------------------------------------
const movable_diagram_map& data_movable()
{
    static const movable_diagram_map db = []()
    {
        movable_diagram_map m;

        merge_into(m, maj_movable());
        merge_into(m, min_movable());
        merge_into(m, aug_movable());
        merge_into(m, dim_movable());
        merge_into(m, sus2_movable());
        merge_into(m, sus4_movable());

        return m;
    }();

    return db;
}

} // namespace chord::database