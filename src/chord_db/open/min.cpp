#include <musical/chord_db/open/min.h>

namespace chord::db
{

const open_diagram_map& min_open()
{
    using D = Diagram;
    using musical::core::Tone;    
    using F = musical::core::guitar::Finger;            

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // MINEUR
        // ========================

        { { Tone::A, TRIAD_MIN },
            {
            // x 0       0 
            // =========== 
            // | | | | 1 | 
            // | | 2 3 | |
            // | | | | | |
            D({ X, 0, 2, 2, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::MIDDLE, F::RING,  F::INDEX })
            }
        },
        { { Tone::C, TRIAD_MIN },
            {
            // x     0    
            // =========== 
            // | | 1 | 2 | 
            // | | | | | |
            // | 3 | | | 4 
            D({ X, 3, 1, 0, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::INDEX, F::MIDDLE, F::PINKY   }),
            }
        },
        { { Tone::D, TRIAD_MIN },
            {
            // x x 0    
            // =========== 
            // | | | | | 1 
            // | | | 2 | |
            // | | | | 3 |

            D({ X, X, 0, 2, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::MIDDLE, F::RING, F::INDEX }),
            }
        },
        { { Tone::E, TRIAD_MIN },
            {
            // 0     0 0 0    
            // =========== 
            // | | | | | |
            // | 2 3 | | |
            // | | | | | |

            D({ 0, 2, 2, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::MIDDLE, F::RING    }),
            }
        },
        { { Tone::G, TRIAD_MIN },
            {
            // x   0 0 0
            // =========== 
            // | 1 | | | |
            // | | | | | |
            // 2 | | | 3 4
            D({ 3, 1, 0, 0, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::MIDDLE, F::INDEX, F::RING, F::PINKY   }),
            }
        },

        // ========================
        // 7
        // ========================
        { { Tone::C, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            // cmin7/Bb
            // x     0
            // =========== 
            // | 1 2 | 3 |
            // | | | | | |
            // | | | | | 4
            D({ X, 1, 1, 0, 1, 3 }, GuitarStandardTuning::B, D::CAGED::C,
                0,
                { F::INDEX, F::MIDDLE, F::RING, F::PINKY   }),
            }
        },
        { { Tone::A, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            // x 0   0   0
            // =========== 
            // | | | | 1 |
            // | | 2 | | |
            // | | | | | |
            D({ X, 0, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::MIDDLE, F::INDEX    }),
            }
        },
        { { Tone::D, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            // x x 0    
            // =========== 
            // | | | | 1 2
            // | | | 3 | |
            // | | | | | |

            D({ X, X, 0, 2, 1, 1 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::RING, F::INDEX, F::MIDDLE }),
            }
        },
        { { Tone::E, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            // 0   0 0 0 0  
            // =========== 
            // | | | | | |
            // | 2 | | | |
            // | | | | | |

            D({ 0, 2, 0, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::MIDDLE    }),
            }
        },
        { { Tone::G, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            //     0 0 
            // =========== 
            // | 2 | | | 1
            // | | | | | |
            // 3 | | | 4 |
            D({ 3, 1, 0, 0, 3, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::RING, F::MIDDLE, F::PINKY, F::INDEX   }),
            }
        }
    };

    return db;
}

} // namespace chord::db