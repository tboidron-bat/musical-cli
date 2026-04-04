#include <musical/chord_db/open/aug.h>

namespace chord::db
{

const open_diagram_map& aug_open()
{
    using D = Diagram;
    using musical::core::Tone;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // AUGMENTED
        // ========================

        { { Tone::A, TRIAD_AUG },
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
        { { Tone::C, TRIAD_AUG },
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
        { { Tone::D, TRIAD_AUG },
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
        { { Tone::E, TRIAD_AUG },
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
        { { Tone::G, TRIAD_AUG },
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

} // namespace chord::db