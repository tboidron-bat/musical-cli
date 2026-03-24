#include <musical/guitar_chord_database/open/aug.h>

namespace chord::database
{

const open_diagram_map& aug_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // AUGMENTED
        // ========================

        { { Note::A, TRIAD_AUG },
            {
            // a:aug
            // x 0     
            // =========== 
            // | | | | | 1
            // | | | 3 2 | 
            // | | 4 | | |

            D({ X, 0, 3, 2, 2, 1 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Note::C, TRIAD_AUG },
            {
            // c:aug
            // x         0
            // =========== 
            // | | | 2 1 |
            // | | 3 | | |
            // | 4 | | | |
            D({ X, 3, 2, 1, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Note::D, TRIAD_AUG },
            {
            // d:aug
            // x x 0 
            // =========== 
            // | | | | | |
            // | | | | | 1
            // | | | 2 3 |
            D({ X, X, 0, 3, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Note::E, TRIAD_AUG },
            {
            // e:aug
            // 0         0
            // =========== 
            // | | | 1 2 |
            // | | 3 | | |
            // | 4 | | | |
            D({ 0, 3, 2, 1, 1, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Note::G, TRIAD_AUG },
            {
            // g:aug
            //       0 0
            // =========== 
            // | | 1 | | |
            // | 2 | | | |
            // 3 | | | | 4
            D({ 3, 2, 1, 0, 0, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        }
    };

    return db;
}

} // namespace chord::database