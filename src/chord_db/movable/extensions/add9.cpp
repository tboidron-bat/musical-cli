#include <musical/chord_db/movable/extensions/add9.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& add9_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // ADD9 TRIAD (0, 4, 7, 14)
        // ========================================================
        {
            (TRIAD_MAJ | (1ULL << 14)), 
            {
                // x     
                // | | | 1 | |
                // | | | | | |
                // | | 2 | | |
                // | 3 | | 4 |
                D({ X, 3, 2, BASE, 3, X }, GuitarStandardTuning::A, D::CAGED::C),

                // x     
                // | 1 1 1 1 1
                // | | | | | |
                // | | 2 | 3 |
                // | | | | | |
                // | | | 4 | |
                D({ X, BASE, 2, 4, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                //           x     
                // 1 1 1 1 1 |
                // | | | | | |
                // | 2 | 3 | |
                // 4 | | | | |
                // | | | | | |                
                D({ 3, 2, BASE, 2, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                // x x             
                // | | 1 | | |
                // | | | | | |
                // | | | 2 | 3
                // | | | | | |
                // | | | | 4 |                
                D({ X, X, BASE, 2, 4, 2 }, GuitarStandardTuning::D, D::CAGED::D),



            }
        },

        // ========================================================
        // ADD9 (sans quinte explicite, tolérance voicing)
        // ========================================================
        {
            (TRIAD_MAJ_NO5 | (1ULL << 14)), 
            {

                // x         x
                // | | 1 | | |
                // | 2 | | 3 |
                // | | | | | |
                // | | | 4 | |

                D({ X, 2, BASE, 3, 2, X }, GuitarStandardTuning::A, D::CAGED::C),
            }
        }

    };

    return db;
}

} // namespace chord::db