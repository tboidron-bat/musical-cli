#include <musical/guitar_chord_database/open/sus4.h>

namespace chord::database
{

const open_diagram_map& sus4_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // SUS4
        // ========================

        { { Note::A, TRIAD_SUS4 },
            {
            // a:sus4
            // x 0 2 2 3 0
            D({ X, 0, 2, 2, 3, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Note::C, TRIAD_SUS4 },
            {
            // c:sus4 (approximation open)
            // x 3 3 0 1 1
            D({ X, 3, 3, 0, 1, 1 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Note::D, TRIAD_SUS4 },
            {
            // d:sus4
            // x x 0 2 3 3
            D({ X, X, 0, 2, 3, 3 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Note::E, TRIAD_SUS4 },
            {
            // e:sus4
            // 0 2 2 2 0 0
            D({ 0, 2, 2, 2, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Note::G, TRIAD_SUS4 },
            {
            // g:sus4
            // 3 3 0 0 1 3
            D({ 3, 3, 0, 0, 1, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        }
    };

    return db;
}

} // namespace chord::database        
        
        
        
        // { "e:7:sus4", 
            //{           
            //0       0 x 
            // =========== 
            //      .       
            //      .    
            //      .    
            // | 1 2 3 | | <-- VII fr.
            // | | | | | |
            //D({ 0, 7, 7, 7, 0, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            //}

