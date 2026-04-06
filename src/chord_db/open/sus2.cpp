#include <musical/chord_db/open/sus2.h>

namespace chord::db
{

const open_diagram_map& sus2_open()
{
    using D = Diagram;
    using musical::core::Tone;    
    using F = musical::core::guitar::Finger;            

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // SUS2
        // ========================

        { { Tone::A, TRIAD_SUS2 },
            {
            // x 0     0 0
            // =========== 
            // | | | | | |
            // | | 1 2 | | 
            // | | | | | |
            D({ X, 0, 2, 2, 0, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::INDEX, F::MIDDLE })
            }
        },
        { { Tone::C, TRIAD_SUS2 },
            {

            // x   0 0 
            // =========== 
            // | | | | 1 |
            // | | | | | | 
            // | 3 | | | 4
            D({ X, 3, 0, 0, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::INDEX, F::PINKY })
            }
        },
        { { Tone::D, TRIAD_SUS2 },
            {
            // x   0     0
            // =========== 
            // | | | | | |
            // | | | 2 | | 
            // | | | | 3 |
            D({ X, X, 0, 2, 3, 0 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::MIDDLE, F::RING }),
            }
        },
        { { Tone::E, TRIAD_SUS2 },
            {
            // 0       0 0
            // =========== 
            // | | | | | |
            // | 1 | | | | 
            // | | | | | |
            // | | 3 4 | |
            D({ 0, 2, 4, 4, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::INDEX, F::RING, F::PINKY })
            }
        },
        { { Tone::G, TRIAD_SUS2 },
            {
            //   0 0 0
            // =========== 
            // | | | | | |
            // | | | | | | 
            // 1 | | | 3 4
            D({ 3, 0, 0, 0, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::INDEX, F::RING, F::PINKY })
            }
        },




        // ========================
        // SUS2 7
        // ========================

        { { Tone::A, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // a:sus2:7
            // x 0   0 0 0
            // =========== 
            // | | | | | |
            // | | 1 | | | 
            // | | | | | |
            D({ X, 0, 2, 0, 0, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::INDEX })
            }
        },
        { { Tone::C, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // C:sus2:7
            // x   0   0 0
            // =========== 
            // | | | | 1 |
            // | | | | | | 
            // | 2 | 3 | 4
            D({ X, 3, 0, 3, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::MIDDLE, F::RING, F::INDEX, F::PINKY })
            }
        },
        { { Tone::D, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // d:sus2:7
            // x x 0     0
            // =========== 
            // | | | | 1 |
            // | | | 2 | | 
            // | | | | | |
            D({ X, X, 0, 2, 1, 0 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::MIDDLE, F::INDEX })
            }
        },
        { { Tone::E, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // e:sus2:7
            // 0         0
            // =========== 
            // | | | | | |
            // | 1 | | | | 
            // | | | | 2 |
            // | | 3 4 | |
            D({ 0, 2, 4, 4, 3, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::INDEX, F::RING, F::PINKY, F::MIDDLE })
            }
        },
        { { Tone::G, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // g:sus2:7 
            //   0 0 0
            // =========== 
            // | | | | | 1
            // | | | | | | 
            // 3 | | | 4 |
            D({ 3, 0, 0, 0, 3, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::RING, F::PINKY, F::INDEX })
            }
        },

        // ========================
        // SUS2 7M
        // ========================


        { { Tone::A, (TRIAD_SUS2 | (1ULL << 11)) },
            {
                // a:sus2:7M
                // x  0    0 0
                // =========== 
                // | | | 1 | |
                // | | 2 | | | 
                // | | | | | |
                D({ X, 0, 2, 1, 0, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                    0,
                    { F::MIDDLE , F::INDEX  })    
            }
        },
        { { Tone::D, (TRIAD_SUS2 | (1ULL << 11)) },
            {
                // d:sus2:7M 
                // x  0    0 0
                // =========== 
                // | | | | | |
                // | | | 1 2 | 
                // | | | | | |
                D({ X, X, 0, 2, 2, 0 }, GuitarStandardTuning::D, D::CAGED::D,
                    0,
                    { F::INDEX, F::MIDDLE })
            }
        },
        { { Tone::G, (TRIAD_SUS2 | (1ULL << 11)) },
            {
                // g:sus2:7M
                // x  0    0 0
                // =========== 
                // | | | | | |
                // | | | | | 1
                // 2 | | | 3 |
                D({ 3, 0, 0, 0, 3, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                    0,
                    { F::MIDDLE, F::RING, F::INDEX })
        }
    }                       
                
    };

    return db;
}

} // namespace chord::db