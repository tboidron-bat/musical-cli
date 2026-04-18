#include <musical/chord_db/movable/database.h>

#include <musical/chord_db/movable/triads/maj.h>
#include <musical/chord_db/movable/triads/min.h>
#include <musical/chord_db/movable/triads/aug.h>
#include <musical/chord_db/movable/triads/sus2.h>

#include <musical/chord_db/movable/sevenths/dominant7.h>
#include <musical/chord_db/movable/sevenths/maj7.h>
#include <musical/chord_db/movable/sevenths/min7.h>
#include <musical/chord_db/movable/sevenths/dominant7_sus2.h>
#include <musical/chord_db/movable/sevenths/maj7_sus2.h>

#include <musical/chord_db/movable/altered/maj7_b5.h>
#include <musical/chord_db/movable/altered/aug_maj7.h>
#include <musical/chord_db/movable/altered/aug_7.h>

#include <musical/chord_db/movable/extensions/min7add11.h>

#include <musical/chord_db/movable/dim.h>

#include <musical/chord_db/movable/sus4.h>
#include <musical/chord_db/movable/extensions/add9.h>
#include <musical/chord_db/movable/extensions/maj9.h>
#include <musical/chord_db/movable/extensions/maj13_sus2.h>

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
// Global movable DB
// ------------------------------------------------------------
const movable_diagram_map& data_movable()
{
    static const movable_diagram_map db = []()
    {
        movable_diagram_map m;

        //TRIADS
        merge_into(m, maj_movable());
        merge_into(m, min_movable());         
        merge_into(m, aug_movable());                
        merge_into(m, dim_movable());        
        merge_into(m, sus2_movable());
        merge_into(m, sus4_movable());

        //SEVENTHS
        merge_into(m, dominant7_movable());
        merge_into(m, min7_movable()); 
        merge_into(m, maj7_movable());        
        merge_into(m, dominant7_sus2_movable());                
        merge_into(m, maj7_sus2_movable());                        

        //EXTENSIONS
        merge_into(m, add9_movable());                
        merge_into(m, maj9_movable());                
        merge_into(m, min7add11_movable());                        
        merge_into(m, maj13_sus2_movable());                                

        //ALTERED
        merge_into(m, maj7_b5_movable());        
        merge_into(m, aug_maj7_movable());
        merge_into(m, aug_7_movable());        


        return m;
    }();

    return db;
}

} // namespace chord::db