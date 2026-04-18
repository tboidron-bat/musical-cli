#include <musical/chord_db/movable/extensions/min7add11.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& min7add11_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // MINOR 7 ADD11
        // ========================================================
        {
            (TRIAD_MIN | (1ULL << 10) | (1ULL << 17)),
            {          
                // | 1 1 1 1 1 
                // | | | | | |
                // 2 | 3 4 | | 
                // | | | | | | 
                // T 3m  3m  7
                //     7   11                     
                D({ 2, BASE, 2, 2, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G),


                // 1 1 1 1 1 1
                // | | | | | |
                // | 2 | | | |
                // | | | | | |
                // | | | | | |
                // | | | | | 4
                D({ BASE, 2, BASE, BASE, BASE, 5 }, GuitarStandardTuning::LOW_E, D::CAGED::E)

                //no D::CAGED::D shape

            }
        },
        {
            (TRIAD_MIN_NO5 | (1ULL << 10) | (1ULL << 17)),
            {          
                // x          
                // | 1 1 1 1 1 
                // | | | | | |
                // | 2 | 3 | |
                // | | | | | |                        
                //   T 3m  T 11
                //       7 
                D({ X, 2, BASE, 2, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::C),

                // x   x       
                // | | | | | 1                        
                // | | | | | |                        
                // | 1 | 3 | | 
                // | | | | 4 |
                D({ X, 2, X, 2, 3, BASE }, GuitarStandardTuning::A, D::CAGED::A),

            }
        }
    };

    return db;
}

} // namespace chord::db