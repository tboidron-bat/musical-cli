#include <musical/guitar_chord_database/open/database.h>

// modules
#include <musical/guitar_chord_database/open/maj.h>
#include <musical/guitar_chord_database/open/min.h>
#include <musical/guitar_chord_database/open/aug.h>
#include <musical/guitar_chord_database/open/dim.h>
#include <musical/guitar_chord_database/open/sus2.h>
#include <musical/guitar_chord_database/open/sus4.h>

namespace chord::database
{

// ------------------------------------------------------------
// Merge util (local au cpp)
// ------------------------------------------------------------
static void merge_into(
    open_diagram_map& dst,
    const open_diagram_map& src)
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
const open_diagram_map& data_open()
{
    static const open_diagram_map db = []()
    {
        open_diagram_map m;

        merge_into(m, maj_open());
        merge_into(m, min_open());
        merge_into(m, aug_open());
        merge_into(m, dim_open());
        merge_into(m, sus2_open());
        merge_into(m, sus4_open());

        return m;
    }();

    return db;
}

} // namespace chord::database