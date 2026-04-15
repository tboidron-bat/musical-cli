#include <musical/chord_db/movable/sevenths/maj7.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj7_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // ▲7 (1 3M 5 7M)
        // ========================================================
        {
            MAJ7,
            {
                // x
                // | | | | | |
                // | | | 1 1 1
                // | | | | | |
                // | | 3 | | |
                // | 4 | | | |
                D({ X, 3, 2, BASE, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::C),

                // x
                // | 1 1 1 1 1 
                // | | | 2 | |
                // | | 3 | 4 | 
                // | | | | | |
                D({ X, BASE, 2, 1, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                // | | 1 1 1 |
                // | | | | | |
                // | 2 | | | 3
                // 4 | | | | |
                D({ 3, 2, BASE, BASE, BASE, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G),


                // | | | | | |
                // 1 1 1 1 1 1 
                // | | 2 3 | |
                // | 4 | | | |
                // | | | | | |

                D({ BASE, 2, 1, 1, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x
                // | | 1 | | | 
                // | | | | | |
                // | | | 2 2 2
                // | | | | | |
                D({ X, X, BASE, 2, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D),

            }
        },

        // ========================================================
        // ▲ (sans quinte)
        // ========================================================
        {
            MAJ7_NO5,
            {
            }
        },
        // ========================================================
        // ▲ 6/9 (neuvième = seconde)
        // ========================================================
        {
            (MAJ7_NO5 | (1ULL << 2) | (1ULL << 9) ),
            {
                // x
                // | | 1 1 1 1            
                // | | | | | |            
                // | | | 3 | |            
                // | 4 | | | |            
                //   T 2 6 ▲ 3M
                D({ X, 3, BASE, 2, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::C)
            }
        },

        // ========================================================
        // ▲ 6/9
        // ========================================================
        {
            (MAJ7 | (1ULL << 9) | (1ULL << 14)),
            {

                // | 1 1 1 1 1
                // 2 | | | 3 |
                // | | | | | |
                // T   6 9 5 ▲
                //  3M
                D({ 1, BASE, BASE, BASE, 1, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },
        // ========================================================
        // ▲ 6/9 (sixième = trezième)
        // ========================================================
        {
            (MAJ7_NO5 | (1ULL << 9) | (1ULL << 14) | (1ULL << 21)),
            {
                // 1 1 1 1 1 1
                // 2 | | | | |            
                // | | 3 | | |            
                // | | | | 4 |                        
                // T   ▲ 9   T
                //   3M    13
                D({ 1, BASE, 2, BASE, 3, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G), //&CAGED:E 

                // 1 | | | | |            
                // | | 2 3 | |            
                // | | | | 4 4            
                // | | | | | |            
                // T   ▲ 3M  9
                //         13
                D({BASE, X, 1, 1, 2, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                //   x     
                // | | | | 1 1
                // | | | | | |
                // | | | 2 | |
                // 3 | | | | |
                // | | 4 | | |
                // T   ▲ 9 3M
                //           13        
                D({ 3, X, 4, 2, 1, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::E) //& CAGED::G
            }
        }

    };

    return db;
}

} // namespace chord::db