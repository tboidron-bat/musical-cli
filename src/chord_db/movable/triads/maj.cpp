#include <musical/chord_db/movable/triads/maj.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        {
            TRIAD_MAJ,
            {
                // | | | | | |
                // | 1 1 1 1 1
                // | | | | 2 |
                // | | 3 | | |
                // | 4 | | | |
                D({ X, 3, 2, BASE, 1, BASE }, GuitarStandardTuning::A, D::CAGED::C),


                // | 1 1 1 1 1 
                // | | | | | |
                // | | 2 3 4 | 
                // | | | | | |
                D({ X, BASE, 2, 2, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                // | | | | | |
                // 1 1 1 1 1 1
                // | | | | | |
                // | 2 | | | |
                // 3 | | | | 4
                D({ 3, 2, BASE, BASE, BASE, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                // | | | | | |
                // 1 1 1 1 1 1 
                // | | | 2 | |
                // | 4 3 | | |
                // | | | | | |
                D({ BASE, 2, 2, 1, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x
                // | | 1 | | | 
                // | | | | | |
                // | | | 2 | 3
                // | | | | 4 |
                D({ X, X, BASE, 2, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D)


            }
        }
    };

    return db;
}
}
