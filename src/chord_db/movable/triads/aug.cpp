#include <musical/chord_db/movable/triads/aug.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& aug_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;
    using F = musical::core::guitar::Finger;        

    static const movable_diagram_map db =
    {
        // ========================================================
        // AUGMENTED TRIAD
        // ========================================================
        {
            TRIAD_AUG,
            {   
                // x         x
                // | | | 1 2 |
                // | | 3 | | | 
                // | 4 | | | |
        
                D({ X, 2, 1, BASE, BASE, X }, GuitarStandardTuning::A, D::CAGED::C,
                1, 
                { F::PINKY, F::RING, F::INDEX, F::MIDDLE })
                ,
                // x         x
                // | 1 | | | |
                // | | | | | | 
                // | | | 2 3 |
                // | | 4 | | |                
                D({ X, BASE, 3, 2, 2, X }, GuitarStandardTuning::A, D::CAGED::A,
                1,
                { F::INDEX, F::PINKY, F::MIDDLE, F::RING })
                ,
                //           x
                // 1 1 1 1 1 |
                // | | 2 | | | 
                // | 3 | | | |
                // 4 | | | | |                
                D({ 3, 2, 1, BASE, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                1,
                { F::PINKY, F::MIDDLE, F::RING, F::INDEX, F::INDEX })
                ,
                //       x x
                // 1 | | | | |
                // | | | 2 | | 
                // | | 3 | | |                
                // | 4 | | | |
                D({ BASE, 3, 2, 1, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                1,
                { F::INDEX, F::MIDDLE, F::RING, F::PINKY })
                ,
                // x x
                // | | 1 | | | 
                // | | | | | |
                // | | | | | 2
                // | | | 3 4 |
                D({ X, X, BASE, 3, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D,
                1,
                { F::INDEX, F::RING, F::PINKY, F::MIDDLE })             
            }
        }
    };

    return db;
}

} // namespace chord::db