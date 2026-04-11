#include <musical/chord_db/movable/aug.h>

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
        },

        // ========================================================
        // AUG MAJ7 ou +Δ7
        // ========================================================
        {
            (TRIAD_AUG | (1ULL << 11)),
            {
            // | | | | 1 |
            // | | | 2 | |
            // | | 3 | | |
            // | 4 | | | |
            D({ X, 3, 2, 1, BASE, X }, GuitarStandardTuning::A, D::CAGED::C,
            1,
            { F::PINKY, F::RING, F::INDEX, F::MIDDLE })
            ,
            // x         x
            // | 1 | | | |
            // | | | 2 | |
            // | | | | 3 |
            // | | 4 | | |
            D({ X, BASE, 3, 1, 2, X }, GuitarStandardTuning::A, D::CAGED::A,
            1,
            { F::INDEX, F::PINKY, F::MIDDLE, F::RING }),

            //         x x
            // | | | 1 | |
            // | | | | | |
            // | | 2 | | |
            // | 3 | | | |
            // 4 | | | | |
            D({ 4, 3, 2, BASE, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G,
            1,
            { F::PINKY, F::MIDDLE, F::RING, F::INDEX}),

            //         x x
            // 1 | | | | |
            // | | 2 3 | |
            // | | | | | |
            // | 4 | | | |
            D({ BASE, 3, 1, 1, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::E,
            1,
            { F::INDEX, F::PINKY, F::MIDDLE, F::RING }),

            // x x
            // | | 1 | | |
            // | | | | | |
            // | | | | 2 3
            // | | | 4 | |
            D({ X, X, BASE, 3, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D,
            1,
            { F::INDEX, F::PINKY, F::MIDDLE, F::RING })
            }
        }
        ,
        {
        // ========================================================
        // AUG 7 ou +7
        // ========================================================

            (TRIAD_AUG | (1ULL << 10)),
            {
            // x         x
            // | | | | 1 |
            // | | | | | |
            // | | | 2 | |
            // | | 3 | | |
            // | 4 | | | |
            D({ X, 4, 3, 2, BASE, X }, GuitarStandardTuning::A, D::CAGED::C,
            1,
            { F::PINKY, F::RING, F::MIDDLE, F::INDEX }),

            // x
            // | 1 1 1 1 |
            // | | | | | |
            // | | | | 3 |
            // | | 4 | | |
            D({ X, BASE, 3, BASE, 2, X }, GuitarStandardTuning::A, D::CAGED::A,
            1,
            { F::INDEX, F::PINKY, F::INDEX, F::RING })
            ,
            //       x   x
            // | 2 | | | |
            // 1 | 3 | | |
            // | | | | 4 |
            D({ 1, BASE, 1, X, 2, X }, GuitarStandardTuning::LOW_E, D::CAGED::G,
            1,
            { F::INDEX, F::MIDDLE, F::RING, F::PINKY }),

            // ========================================================
            // CAGED E
            // ========================================================
            //   x       x
            // 1 | 2 | | |
            // | | | 3 4 |
            // | | | | | |
            // | | | | | |
            D({ BASE, X, BASE, 1, 1, X }, GuitarStandardTuning::LOW_E, D::CAGED::E,
            0,
            { F::INDEX, F::MIDDLE, F::RING, F::PINKY }),

            // x x
            // | | 1 | | |
            // | | | | 2 |
            // | | | | | 3
            // | | | 4 | |
            D({ X, X, BASE, 3, 1, 2 }, GuitarStandardTuning::D, D::CAGED::D,
            0,
            { F::INDEX, F::PINKY, F::MIDDLE, F::RING })

            }        
        }
    };

    return db;
}

} // namespace chord::db