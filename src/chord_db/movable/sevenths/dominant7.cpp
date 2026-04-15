#include <musical/chord_db/movable/sevenths/dominant7.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& dominant7_movable()
{
    constexpr IntervalMask TRIAD_MAJ =
        (1ULL << 4) | (1ULL << 7);

    constexpr IntervalMask TRIAD_MAJ_NO5 =
        (1ULL << 4);


    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        {
            (TRIAD_MAJ | (1ULL << 10)),
            {   
                // x       x
                // | | | | | | 
                // | | 1 | | | 
                // | 2 | 3 | 4 
                D({ X, 2, 1, 2, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::C),

                // x
                // | 1 1 1 1 1 
                // | | | | | |
                // | | 2 | 4 |
                // | | | | | |
                D({ X, BASE, 2, BASE, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                // | | | | | |
                // 1 1 1 1 1 1
                // | | | | | 2
                // | 3 | | | |
                // 4 | | | | |
                D({ 3, 2, BASE, BASE, BASE, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                // 1 1 1 1 1 1 
                // | | | 2 | |
                // | 4 | | | |
                // | | | | | |
                D({ BASE, 2, BASE, 1, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                // x x
                // | | 1 | | | 
                // | | | | 2 |
                // | | | 3 | 4
                // | | | | | |
                D({ X, X, BASE, 2, 1, 2 }, GuitarStandardTuning::D, D::CAGED::D)
            }        
        },
        {
            (TRIAD_MAJ_NO5 | (1ULL << 10)),
            {   
                // x         x
                // | | | | 1 | 
                // | | 2 | | | 
                // | 3 | 4 | | 
                D({ X, 2, 1, 2, BASE, X }, GuitarStandardTuning::A, D::CAGED::C)
            }
        }
    };

    return db;
}

}