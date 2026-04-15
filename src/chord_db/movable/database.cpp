#include <musical/chord_db/movable/database.h>

// modules
#include <musical/chord_db/movable/triads/maj.h>
#include <musical/chord_db/movable/altered/maj7_b5.h>
#include <musical/chord_db/movable/sevenths/dominant7.h>
#include <musical/chord_db/movable/sevenths/maj7.h>

#include <musical/chord_db/movable/min.h>
#include <musical/chord_db/movable/aug.h>
#include <musical/chord_db/movable/dim.h>
#include <musical/chord_db/movable/sus2.h>
#include <musical/chord_db/movable/sus4.h>
#include <musical/chord_db/movable/extensions/add9.h>
#include <musical/chord_db/movable/extensions/maj9.h>

namespace chord::db
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
        merge_into(m, maj7_movable());
        merge_into(m, maj7_b5_movable());
        merge_into(m, dominant7_movable());
        
        merge_into(m, min_movable());
        merge_into(m, aug_movable());
        merge_into(m, dim_movable());
        merge_into(m, sus2_movable());
        merge_into(m, sus4_movable());
        merge_into(m, add9_movable());
        merge_into(m, maj9_movable());

        return m;
    }();

    return db;
}

} // namespace chord::db