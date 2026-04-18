#include <musical/chord_db/movable/altered/aug_maj7.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& aug_maj7_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;
    using F = musical::core::guitar::Finger;        

    static const movable_diagram_map db =
    {
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
    };

    return db;
}

} // namespace chord::db