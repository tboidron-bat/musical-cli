#include <musical/chord_db/movable/sus4.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& sus4_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // SUS4 TRIAD
        // ========================================================
        {
            SUS4,
            {
                // (forme A)
                // x
                // | 1 1 1 1 1
                // | | | | | |
                // | | 2 3 | |
                // | | | | 4 |
                D({ X, BASE, 2, 2, 3, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                // (forme D)
                // x x
                // | | 1 1 1 1
                // | | | | | |
                // | | | 2 | |
                // | | | | 3 4
                D({ X, X, BASE, 2, 3, 3 }, GuitarStandardTuning::D, D::CAGED::D),

                // (forme E)
                // | | | | | |
                // 1 1 1 1 1 1
                // | | | | | |
                // | 2 3 4 | |
                // | | | | | |
                D({ BASE, 2, 2, 2, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E)
            }
        },

        // ========================================================
        // 7 (dominant sus4)
        // ========================================================
        { {  SUS4 | (1ULL << 10)},
            {
            // x     
            // =========== 
            // | 1 1 1 1 1
            // | | | | | | 
            // | 3 3 3 | |
            D({ X, 3, 3, 3, 1, 1 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        }

    };

    return db;
}

} // namespace chord::db