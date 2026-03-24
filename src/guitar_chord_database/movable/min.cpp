#include <musical/guitar_chord_database/movable/min.h>

namespace chord::database
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
        // MINOR 7
        // ========================================================
        {
            (TRIAD_MIN | (1ULL << 10)),
            {
                // x          
                // | 1 1 1 1 1 
                // | | | | | |
                // | 2 | 3 | 4
                // | | | | | |                        
                D({ X, 2, BASE, 2, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::C)
            }
        },

        // ========================================================
        // MINOR 7 NO 5
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
        }
    };

    return db;
}

} // namespace chord::database