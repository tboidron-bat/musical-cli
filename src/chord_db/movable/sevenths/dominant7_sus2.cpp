#include <musical/chord_db/movable/sevenths/dominant7_sus2.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& dominant7_sus2_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // 7SUS2 
        // ========================================================
        {
            (SUS2_TRIAD | (1ULL << 10)),
            {
                // x       x
                // | | 1 | | |
                // | | | | | |
                // | | | | | |
                // | 2 | 3 | 4
                D({ X, 3, BASE, 3, X, 3 }, GuitarStandardTuning::A, D::CAGED::C),

                // x         x
                // | | | | 1 |
                // | | 2 3 | |
                // | | | | | |
                // | | | | | |
                // | 4 | | | |
                D({ X, 4, 1, 1, BASE, X }, GuitarStandardTuning::A, D::CAGED::C),


                // x     
                // | 1 1 1 1 1
                // | | | | | |                                                                                                                                                                              
                // | | 2 | | |            
                // | | | | | |
                D({ X, BASE, 2, BASE, BASE,BASE }, GuitarStandardTuning::A, D::CAGED::A),

                //           x    
                // | 1 1 1 | |
                // | | | | | |
                // | | | | | |            
                // 2 | 3 | 4 |
                D({ 3, BASE, 3, BASE, 3, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                //   x       x
                // | | | 1 | |  
                // 2 | 3 | 4 |               
                // | | | | | |  
                D({ 1, X, 1, BASE, 1, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                //   x   x
                // 1 | 2 | 3 |               
                // | | | | | |  
                // | | | | | 4
                // | | | | | |
                D({ BASE, X, BASE, X, BASE, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x    
                // | | 1 1 1 1
                // | | | | 2 |
                // | | | 3 | |            
                // | | | | | |
                D({ X, X, BASE, 2, 1, BASE }, GuitarStandardTuning::D, D::CAGED::D)
            }
        }
        ,
        {
            (SUS2_NO5 | (1ULL << 10)),
            {
                // x         x
                // | | 1 | | |
                // | | | | 2 |
                // | | | | | |
                // | 3 | 4 | |
                D({ X, 3, BASE, 3, 1, X }, GuitarStandardTuning::A, D::CAGED::C),
            }
        }
    };

    return db;
}

} // namespace chord::db