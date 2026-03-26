#include <musical/guitar_chord_database/open/sus2.h>

namespace chord::database
{

const open_diagram_map& sus2_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // SUS2
        // ========================

        { { NoteEnum::A, TRIAD_SUS2 },
            {
            // x 0     0 0
            // =========== 
            // | | | | | |
            // | | 1 2 | | 
            // | | | | | |
            D({ X, 0, 2, 2, 0, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { NoteEnum::C, TRIAD_SUS2 },
            {

            // x   0 0 
            // =========== 
            // | | | | 1 |
            // | | | | | | 
            // | 3 | | | 4
            D({ X, 3, 0, 0, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { NoteEnum::D, TRIAD_SUS2 },
            {
            // x   0     0
            // =========== 
            // | | | | | |
            // | | | 2 | | 
            // | | | | 3 |
            D({ X, X, 0, 2, 3, 0 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { NoteEnum::E, TRIAD_SUS2 },
            {
            // 0       0 0
            // =========== 
            // | | | | | |
            // | 2 | | | | 
            // | | | | | |
            // | | 4 4 | |
            D({ 0, 2, 4, 4, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { NoteEnum::G, TRIAD_SUS2 },
            {
            //   0 0 0
            // =========== 
            // | | | | | |
            // | | | | | | 
            // 3 | | | 3 3
            D({ 3, 0, 0, 0, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },




        // ========================
        // SUS2 7
        // ========================

        { { NoteEnum::A, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // a:sus2:7
            // x 0   0  0 0
            // =========== 
            // | | | | | |
            // | | 1 | | | 
            // | | | | | |
            D({ X, 0, 2, 0, 0, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { NoteEnum::C, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // C:sus2:7
            // x   0   0 0
            // =========== 
            // | | | | 1 |
            // | | | | | | 
            // | 2 | 3 | 4
            D({ X, 3, 0, 3, 1, 3 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { NoteEnum::D, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // d:sus2:7
            // x x 0     0
            // =========== 
            // | | | | 1 |
            // | | | 2 | | 
            // | | | | | |
            D({ X, X, 0, 2, 1, 0 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { NoteEnum::E, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // e:sus2:7
            // 0       0 0
            // =========== 
            // | | | | | |
            // | 2 | | | | 
            // | | | | | |
            // | | | | | |
            D({ 0, 2, 4, 4, 3, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { NoteEnum::G, (TRIAD_SUS2 | (1ULL << 10)) },
            {
            // g:sus2:7 
            //   0 0 0
            // =========== 
            // | | | | | 1
            // | | | | | | 
            // 3 | | | 3 |
            D({ 3, 0, 0, 0, 3, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },

        // ========================
        // SUS2 7M
        // ========================


        { { NoteEnum::A, (TRIAD_SUS2 | (1ULL << 11)) },
            {
                // a:sus2:7M
                // x  0    0 0
                // =========== 
                // | | | 1 | |
                // | | 2 | | | 
                // | | | | | |
                D({ X, 0, 2, 1, 0, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { NoteEnum::D, (TRIAD_SUS2 | (1ULL << 11)) },
            {
                // d:sus2:7M 
                // x  0    0 0
                // =========== 
                // | | | | | |
                // | | | 1 2 | 
                // | | | | | |
                D({ X, X, 0, 2, 2, 0 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { NoteEnum::G, (TRIAD_SUS2 | (1ULL << 11)) },
            {
                // g:sus2:7M
                // x  0    0 0
                // =========== 
                // | | | | | |
                // | | | | | 1
                // 2 | | | 3 |
                D({ 3, 0, 0, 0, 3, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }
    }                       
                
    };

    return db;
}

} // namespace chord::database