#include <musical/chord_db/movable/sus2.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& sus2_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // SUS2 TRIAD
        // ========================================================
        {
            SUS2,
            {
                // x x    
                // | | 1 1 1 1
                // | | | | | |
                // | | | 2 | |            
                // | | | | 4 |
                D({ X, X, BASE, 2, 3, BASE }, GuitarStandardTuning::D, D::CAGED::D),
                // x     
                // | 1 1 1 1 1
                // | | | | | |
                // | | 2 3 | |            
                // | | | | | |
                D({ X, BASE, 2, 2, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::A)


            }
        },

        // ========================================================
        // SUS2 MAJ7 13
        // ========================================================
        {
            (SUS2 | (1ULL << 11) | (1ULL << 21)),
            {
                // x     
                // | 1 1 1 1 1
                // | | | 2 | |
                // | | 3 | | 4            
                // | | | | | |
                D({ X, BASE, 2, 1, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::A)
            }
        }
    };

    return db;
}

} // namespace chord::db