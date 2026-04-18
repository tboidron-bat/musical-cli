#include <musical/chord_db/movable/triads/sus2.h>

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
            SUS2_TRIAD,
            {
                // x
                // | 1 1 1 1 1
                // | | | | 2 |
                // | | | | | |
                // | 3 | | | 4
                D({ X, 3, BASE, BASE, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C),

                // x     
                // | 1 1 1 1 1
                // | | | | | |                                                                                                                                                                              
                // | | 2 3 | |            
                // | | | | | |
                D({ X, BASE, 2, 2, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                //         x x    
                // | 1 1 1 | |
                // | | | | | |
                // | | | 3 | |            
                // 4 | | | | |
                D({ 3, BASE, BASE, 2, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                //         x x
                // | | | 1 | |                
                // 2 | | | | |  
                // | | | | | |
                // | 3 4 | | |
                D({ 1, 3, 3, BASE, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x    
                // | | 1 1 1 1
                // | | | | | |
                // | | | 2 | |            
                // | | | | 4 |
                D({ X, X, BASE, 2, 3, BASE }, GuitarStandardTuning::D, D::CAGED::D),
            }
        }
    };

    return db;
}

} // namespace chord::db