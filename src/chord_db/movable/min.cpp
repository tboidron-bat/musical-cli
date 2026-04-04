#include <musical/chord_db/movable/min.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& min_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // MINOR TRIAD
        // ========================================================
        {
            TRIAD_MIN,
            {
                // | 1 1 1 1 1
                // | | | | 4 |
                // | | 2 3 | |
                // | | | | | |
                D({ X, BASE, 2, 2, 1, BASE }, GuitarStandardTuning::A, D::CAGED::A)
            }
        },

        // ========================================================
        // 7
        // ========================================================
        {
            (TRIAD_MIN | (1ULL << 10)),
            {
                // x          
                // | 1 1 1 1 1 
                // | | | | | |
                // | 2 | 3 | 4
                // | | | | | |                        
                D({ X, 2, BASE, 2, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::C),
                // x          
                // | 1 1 1 1 1 
                // | | | | 2 |
                // | | 3 | | |
                // | | | | | |                        
                D({ X, BASE, 2, BASE, 1, BASE }, GuitarStandardTuning::A, D::CAGED::A),
                // x          
                // | 1 | | | |
                // | | | | | |
                // 2 | 4 4 4 4
                // | | | | | |                        
                D({ 2, BASE, 2, 2, 2, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
                // /7          
                // | | 1 | | |
                // 2 3 | | | |
                // | | | | | |
                // | | | 4 4 4                        
                D({ 1, 1, BASE, 3, 3, 3 }, GuitarStandardTuning::HIGH_E, D::CAGED::G),
                //           
                // 1 1 1 1 1 1
                // | | | | | |
                // | 2 | | | |
                // | | | | 4 |
                D({ BASE, 2, BASE, BASE, 3, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),
                // x x         
                // | | 1 | | |
                // | | | | 2 3
                // | | | 4 | |
                // | | | | | |
                D({ X, X, BASE, 2, 1, 1 }, GuitarStandardTuning::D, D::CAGED::D)



            }
        },

        // ========================================================
        // 7 NO 5
        // ========================================================
        {
            (TRIAD_MIN_NO5 | (1ULL << 10)),
            {
                // x         x 
                // | | 1 | 2 | 
                // | |   | | |
                // | 3 | 4 | |
                // | |   | | |                        
                D({ X, 2, BASE, 2, BASE, X }, GuitarStandardTuning::A, D::CAGED::C)
            }
        },
        // ========================================================
        // MINOR 7 ADD11
        // ========================================================
        {
            (TRIAD_MIN | (1ULL << 10) | (1ULL << 14)),
            {          
                // 1 1 1 1 1 1 
                // | | | | | |
                // 2 | 3 4 | | 
                // | | | | | |                        
                D({ 2, BASE, 2, 2, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G)
            }
        }
    };

    return db;
}

} // namespace chord::db