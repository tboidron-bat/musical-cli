#include <musical/guitar_chord_database/movable/dim.h>

namespace chord::database
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& dim_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // DIM TRIAD
        // ========================================================
        { ( TRIAD_DIM ),
            {
            // E shape      
            // 1 1 1 1 1 1
            // | 2 | | | |
            // | | 3 | 4 |
            D({ BASE, 1, 2, BASE, 2, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),

            }
        },

        // ========================================================
        // DIM7 
        // ========================================================
        {
            (TRIAD_DIM | (1ULL << 9)), // bb7 (6e enharmonique)
            {
            // dim7 ou rond barré
            // x      
            // | | | 1 | |
            // | 2 | | | |
            // | | 3 | 4 |
            D({ X, 1, 2, BASE, 2, X }, GuitarStandardTuning::A, D::CAGED::C),
            }
        }
    };

    return db;
}

} // namespace chord::database