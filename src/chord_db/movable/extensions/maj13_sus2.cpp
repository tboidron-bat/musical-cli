#include <musical/chord_db/movable/extensions/maj13_sus2.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj13_sus2_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // maj13sus2
        // ========================================================
        {            
            (SUS2_TRIAD | (1ULL << 11) | (1ULL << 21)),
            {
                // x     
                // | | 1 | 1 | |
                // | | | | | | |
                // | | | 2 | | |
                // | 3 | | | 4 |
                D({ X, 3, BASE, 2, BASE, 3 }, GuitarStandardTuning::A, D::CAGED::A),                

                // x     
                // | 1 1 1 1 1
                // | | | 2 | |
                // | | 3 | | 4            
                // | | | | | |
                D({ X, BASE, 2, 1, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::A),

                // 1 1 1 1 1 1
                // | | | | | |
                // | | | | | |            
                // 2 | | | 3 |
                // | | 4 | | |
                D({ 3, BASE, 4, BASE, 3, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                // x     
                // | | | | | |
                // | | | | | |
                // | | | | | |
                // | | | | | |

            }
        },
        {
            (SUS2_NO5 | (1ULL << 11) | (1ULL << 21)),
            {
                //         x x    
                // | | | 1 | |
                // | 2 | | | |
                // | | | | | |            
                // | | 3 | | |
                // 4 | | | | |
                D({ 4, 1, 3, BASE, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),
                //   x                           
                // | | | 1 | |
                // 2 | | | | |               
                // | | 3 | | |  
                // | | | | 4 4                      
                D({ 1, X, 2, BASE, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
                // x x    
                // | | 1 | | 1
                // | | | | | |
                // | | | | 3 |            
                // | | | | | |
                // | | | 4 | |                    
                D({ X, X, BASE, 4, 2, BASE }, GuitarStandardTuning::D, D::CAGED::D)
            }
        }

    };

    return db;
}

} // namespace chord::db