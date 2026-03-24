#include <musical/guitar_chord_database/open/min.h>

namespace chord::database
{

const open_diagram_map& min_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // MINEUR
        // ========================

        { { Note::A, TRIAD_MIN },
            {
            D({ X, 0, 2, 2, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Note::C, TRIAD_MIN },
            {
            // x     0   x 
            // =========== 
            // | | 1 | 1 | 
            // | | | | | |
            // | 3 | | | 3 
            D({ X, 3, 1, 0, 1, X }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Note::D, TRIAD_MIN },
            {
            D({ X, X, 0, 2, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Note::E, TRIAD_MIN },
            {
            D({ 0, 2, 2, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Note::G, TRIAD_MIN },
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
        // MIN7
        // ========================

        { { Note::A, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            D({ X, 0, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Note::D, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            D({ X, X, 0, 2, 1, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Note::E, (TRIAD_MIN | ( 1ULL << 10 )) },
            {
            D({ 0, 2, 0, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Note::G, (TRIAD_MIN | ( 1ULL << 10 )) },
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