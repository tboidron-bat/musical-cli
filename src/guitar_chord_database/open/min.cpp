#include <musical/guitar_chord_database/open/min.h>

namespace chord::database
{

const open_diagram_map& min_open()
{
    using D = Diagram;
    using musical::core::Tone;    

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // MINEUR
        // ========================

        { { Tone::A, TRIAD_MIN },
            {
            D({ X, 0, 2, 2, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Tone::C, TRIAD_MIN },
            {
            // x     0   x 
            // =========== 
            // | | 1 | 1 | 
            // | | | | | |
            // | 3 | | | 3 
            D({ X, 3, 1, 0, 1, X }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Tone::D, TRIAD_MIN },
            {
            D({ X, X, 0, 2, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Tone::E, TRIAD_MIN },
            {
            D({ 0, 2, 2, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Tone::G, TRIAD_MIN },
            {
            // x   0 0 0
            // =========== 
            // | 1 | | | |
            // | | | | | |
            // 2 | | | 3 4
            D({ 3, 1, 0, 0, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },

        // ========================
        // 7
        // ========================
        { { Tone::C, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            // x     0
            // =========== 
            // | | 1 | 2 |
            // | | | | | |
            // | 3 | | | 4
            D({ X, 3, 1, 0, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Tone::A, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            // x 0   0   0
            // =========== 
            // | | | | 1 |
            // | | 2 | | |
            // | | | | | |
            D({ X, 0, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Tone::D, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            D({ X, X, 0, 2, 1, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Tone::E, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            D({ 0, 2, 0, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Tone::G, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            //     0 0 
            // =========== 
            // | 1 | | | 2
            // | | | | | |
            // 3 | | | 4 |
            D({ 3, 1, 0, 0, 3, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        }
    };

    return db;
}

} // namespace chord::database