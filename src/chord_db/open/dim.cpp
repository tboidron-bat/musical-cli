#include <musical/chord_db/open/dim.h>

namespace chord::db
{

const open_diagram_map& dim_open()
{
    using D = Diagram;
    using musical::core::Tone;    

    constexpr uint8_t X = D::MUTE;

    // ------------------------------------------------------------
    // INTERVALS
    // ------------------------------------------------------------
    constexpr IntervalMask bb7 = 1ULL << 9; // dim7 (double flat 7), noté (°).

    static const open_diagram_map db =
    {
        // ========================
        // DIM TRIAD
        // ========================

        { { Tone::A, TRIAD_DIM },
            {
            // a:dim
            // x 0       x     
            // =========== 
            // | | 1 | 2 |
            // | | | 3 | |
            // | | | | | |
            D({ X, 0, 1, 2, 1, X }, GuitarStandardTuning::A, D::CAGED::A),
            // x 0            
            // =========== 
            // | | 1 1 1 1
            // | | | 2 | |
            // | | | | | |
            // | | | | | |
            // | | | | | 4                        
            D({ X, 0, 1, 2, 1, 5 }, GuitarStandardTuning::A, D::CAGED::A)
            }
        },
        { { Tone::D, TRIAD_DIM },
            {
            // d:dim
            // x x 0      
            // =========== 
            // | | | 1 | 2
            // | | | | | |
            // | | | | 4 |
            D({ X, X, 0, 1, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Tone::E, TRIAD_DIM },
            {
            // e:dim
            // 0     0   0
            // =========== 
            // | 1 | | | |
            // | | 2 | | |
            // | | | | | |
            // | | | | | |
            // | | | | 4 |
            D({ 0, 1, 2, 0, 5, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        // ========================
        // DIM7 ou rond barré 
        // ========================

        { { Tone::A, (TRIAD_DIM | bb7) },
            {
            // a:dim7
            // x 0     
            // =========== 
            // | | 1 | 3 |
            // | | | 2 | 4
            // | | | | | |
            D({ X, 0, 1, 2, 1, 2 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Tone::D, (TRIAD_DIM | bb7) },
            {
            // d:dim7
            // x x 0   0
            // =========== 
            // | | | 1 | 2
            // | | | | | |
            // | | | | | |
            D({ X, X, 0, 1, 0, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Tone::E, (TRIAD_DIM | bb7) },
            {
            // e:dim7
            // 0     0 
            // =========== 
            // | 1 | | | |
            // | | 2 | 3 |
            // | | | | | |
            D({ 0, 1, 2, 0, 2, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Tone::G, (TRIAD_DIM | bb7) },
            {
            // g:dim7 
            //         x 0
            // =========== 
            // | | | | | |
            // | | 1 | | |
            // 2 | | 3 | |
            // | 4 | | | |
            D({ 3, 4, 2, 3, X, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        }
    };

    return db;
}

} // namespace chord::db

