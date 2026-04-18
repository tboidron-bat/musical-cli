#include <musical/chord_db/movable/triads/min.h>

namespace chord::db
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
                // x         x
                // | | | 1 | |  
                // | | 2 | 3 |
                // | | | | | |
                // | 4 | | | |
                D({ X, 3, 1, BASE, 1, X }, GuitarStandardTuning::A, D::CAGED::C),

                // x
                // | 1 1 1 1 1
                // | | | | 4 |
                // | | 2 3 | |
                // | | | | | |
                D({ X, BASE, 2, 2, 1, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                // | | 1 | | |
                // | 2 | | | |
                // | | | | | |
                // 3 | | 4 4 4
                D({ 3, 1, BASE, 3, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                // 1 1 1 1 1 1
                // | | | | | |
                // | 3 4 | | |
                // | | | | | |
                D({ BASE, 2, 2, BASE, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x
                // | | 1 | | |
                // | | | | | 2
                // | | | 3 | |
                // | | | | 4 |
                D({ X, X, BASE, 2, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D)
            }
        },
    };

    return db;
}
}
