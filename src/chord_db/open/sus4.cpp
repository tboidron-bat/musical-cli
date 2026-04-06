#include <musical/chord_db/open/sus4.h>

namespace chord::db
{

const open_diagram_map& sus4_open()
{
    using D = Diagram;
    using musical::core::Tone;  
    using F = musical::core::guitar::Finger;              

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // SUS4
        // ========================

        { { Tone::A, TRIAD_SUS4 },
            {
            // x 0       0
            // =========== 
            // | | | | | |
            // | | 1 2 | | 
            // | | | | 3 |
            D({ X, 0, 2, 2, 3, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::INDEX, F::MIDDLE, F::RING }
            ),
            }
        },
        { { Tone::C, TRIAD_SUS4 },
            {
            // x     0
            // =========== 
            // | | | | 1 1
            // | | | | | | 
            // | 3 4 | | |
            D({ X, 3, 3, 0, 1, 1 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::PINKY, F::INDEX, F::INDEX })
            }
        },
        { { Tone::D, TRIAD_SUS4 },
            {
            // x x 0 
            // =========== 
            // | | | | | |
            // | | | 2 | | 
            // | | | | 3 4
            D({ X, X, 0, 2, 3, 3 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::MIDDLE, F::RING, F::PINKY })
            }
        },
        { { Tone::E, TRIAD_SUS4 },
            {
            // 0       0 0
            // =========== 
            // | | | | | |
            // | 1 2 3 | | 
            // | | | | | |
            D({ 0, 2, 2, 2, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::INDEX, F::MIDDLE, F::RING })
            }
        },
        { { Tone::G, TRIAD_SUS4 },
            {
            //     0 0
            // =========== 
            // | | | | 1 |
            // | | | | | | 
            // 2 3 | | | 4
            D({ 3, 3, 0, 0, 1, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::MIDDLE, F::RING, F::INDEX, F::PINKY })
            }
        },

        // ========================
        // SUS4 7
        // ========================


        { { Tone::A, TRIAD_SUS4 | (1ULL << 10)},
            {
            // x 0   0   0
            // =========== 
            // | | | | | |
            // | | 1 | | | 
            // | | | | 3 |
            D({ X, 0, 2, 0, 3, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::INDEX, F::RING })
            }
        },
        { { Tone::C, TRIAD_SUS4 | (1ULL << 10)},
            {
            // x     0
            // =========== 
            // | 1 | | | | 3fr 
            // | | | | | | 
            // | | 2 | | | 
            // | | | | 4 4 
            D({ X, 3, 5, 0, 6, 6 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::INDEX, F::MIDDLE, F::PINKY, F::PINKY })
            }
        },
        { { Tone::D, TRIAD_SUS4 | (1ULL << 10)},
            {
            // x x 0 
            // =========== 
            // | | | | 1 |
            // | | | 2 | | 
            // | | | | | 4
            D({ X, X, 0, 2, 1, 3 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::MIDDLE, F::INDEX, F::PINKY })
            }
        },
        { { Tone::E, TRIAD_SUS4 | (1ULL << 10)},
            {
            // 0   0    0 0
            // =========== 
            // | | | | | |
            // | 1 | 2 | | 
            // | | | | | |
            D({ 0, 2, 0, 2, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::INDEX, F::MIDDLE}),

            //e:7:sus4                 
            //0       0 x 
            // =========== 
            //      .       
            //      .    
            //      .    
            // | 1 2 3 | | <-- VII fr.
            // | | | | | |
            D({ 0, 7, 7, 7, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::C //ou D::CAGED::A,
                , 0,
                { F::INDEX, F::MIDDLE, F::RING })
             }            
        },
        { { Tone::G, TRIAD_SUS4 | (1ULL << 10)},
            {
            //     0 0
            // =========== 
            // | | | | 1 1
            // | | | | | | 
            // 3 4 | | | |
            D({ 3, 3, 0, 0, 1, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::RING, F::PINKY, F::INDEX, F::INDEX })
             }
        },

        // ========================
        // 7sus4add13
        // ========================
        { { Tone::A, TRIAD_SUS4 | (1ULL << 10) | (1ULL << 21) },
            {
            // x 0   0 
            // =========== 
            // | | | | | | 
            // | | 1 | | 2 
            // | | | | 3 | 
            D({ X, 0, 2, 0, 3, 2 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::INDEX, F::RING, F::MIDDLE })
             }
        }
    };

    return db;
}

} // namespace chord::db        
