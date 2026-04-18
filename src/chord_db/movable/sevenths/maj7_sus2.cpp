#include <musical/chord_db/movable/sevenths/maj7_sus2.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj7_sus2_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // ▲SUS2 
        // ========================================================
        {
            (SUS2_TRIAD | (1ULL << 11)),
            {
                // x       x
                // | | 1 1 1 |
                // | | | | | |
                // | | | | | |
                // | 2 | | | 4
                D({ X, 3, BASE, BASE, BASE, 3 }, GuitarStandardTuning::A, D::CAGED::C),

                // x     
                // | 1 1 1 1 1
                // | | | 2 | |                                                                                                                                                                              
                // | | 3 | | |            
                // | | | | | |
                D({ X, BASE, 2, 1, BASE,BASE }, GuitarStandardTuning::A, D::CAGED::A),

                //           x    
                // | 1 1 1 | |
                // | | | | | |
                // | | | | | |            
                // 2 | | | 3 |
                // | | 4 | | |
                D({ 3, BASE, 4, BASE, 3, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                //         x x    
                // | | | 1 | |
                // | 2 3 | | |
                // | | | | | |            
                // | | | | | |
                // 4 | | | | |
                D({ 4, 1, 1, BASE, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                //   x       x
                // | | | 1 | |  
                // 2 | | | 3 |               
                // | | 4 | | |  
                D({ 1, X, 2, BASE, 1, X }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                //   x   x
                // 1 | | | 2 |               
                // | | 3 | | |  
                // | | | | | 4
                // | | | | | |
                D({ BASE, X, 1, X, BASE, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x    
                // | | 1 | | 2
                // | | | | | |
                // | | | 3 4 |            
                // | | | | | |
                D({ X, X, BASE, 2, 2, BASE }, GuitarStandardTuning::D, D::CAGED::D)
            }
        }
    };
    return db;
}
} 