#include <musical/guitar_chord_database/open/maj.h>

namespace chord::database
{

const open_diagram_map& maj_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // MAJEUR
        // ========================
        { { Note::A, TRIAD_MAJ},
            {
            //"a:maj",                 
            D({ X, 0, 2, 2, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            // x     0   0
            // =========== 
            // | | | | 1 |
            // | | 2 | | |
            // | 3 | | | |
        }},
        { {Note::C, TRIAD_MAJ},//"c:maj"
            {
            D({ X, 3, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { {Note::D, TRIAD_MAJ}, //"d:maj"
            {
            D({ X, X, 0, 2, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { {Note::E, TRIAD_MAJ}, //"e:maj", 
            {
            D({ 0, 2, 2, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | |
            // 2 | | | | 4
            }
        },
        { {Note::G, TRIAD_MAJ}, //"g:maj", 
            {
            D({ 3, 2, 0, 0, 0, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },

        // ========================
        // DOMINANT 7
        // ========================

        {  { Note::A, (TRIAD_MAJ | (1ULL << 10)) },
            
            {
            //"a:maj:7", 
            D({ X, 0, 2, 0, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        {  { Note::C, ( TRIAD_MAJ | (1ULL << 10)) },
            {
            //"c:maj:7"
            // x         0 
            // =========== 
            // | | | | 1 | 
            // | | 2 | | |
            // | 3 | 3 | |
            D({ X, 3, 2, 3, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Note::D, ( TRIAD_MAJ | (1ULL << 10)) },
            {
            //"d:maj:7"                
            D({ X, X, 0, 2, 1, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Note::E, ( TRIAD_MAJ | (1ULL << 10)) },
            //"e:maj:7" 
            {
            D({ 0, 2, 0, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Note::G, ( TRIAD_MAJ | (1ULL << 10)) },
            //"g:maj:7"
            {
            // x   0 0 0
            // =========== 
            // | | | | | 1
            // | 2 | | | |
            // 3 | | | | |
            D({ 3, 2, 0, 0, 0, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },


        // ========================
        // MAJ7
        // ========================

        { { Note::C, (TRIAD_MAJ | (1ULL << 11)) },
            
            {
            //"c:maj:7M"                
            // x     0 0 0 
            // =========== 
            // | | | | | | 
            // | | 2 | | |
            // | 3 | | | |
            D({ X, 3, 2, 0, 0, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { { Note::D, (TRIAD_MAJ | (1ULL << 11)) },
            //"d:maj:7M"
            {
            D({ X, X, 0, 2, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { { Note::E, (TRIAD_MAJ | (1ULL << 11)) },
            //"e:maj:7M"
            {
            D({ 0, 2, 1, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { { Note::G, (TRIAD_MAJ | (1ULL << 11)) },
            {
            //"g:maj:7M"
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | 3
            // 2 | | | | |

            D({ 3, 2, 0, 0, 0, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },

        // ========================
        // ========================

        { { Note::A, (TRIAD_MAJ | (1ULL << 6) | (1ULL << 10) ) },
            {
            //"a:maj:7:b5", 
            // x 0       x
            // ===========
            // | | 1 2 | |
            // | | | | 3 |
            // | | | | | |
            // | | | | | |
            D({ X, 0, 1, 1, 2, X }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { { Note::D, (TRIAD_MAJ_NO5 | (1ULL << 5)) },
            
            {
            //"d:maj:add4:no5",                 
            //     0 0 x x
            // =========== 
            //      .       
            //      .    
            //      .    
            // | 1 | | | | <-- 9 frette
            // 2 | | | | |
            D({ 10, 9, 0, 0, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },
        { { Note::C, (TRIAD_MAJ | (1ULL << 11) | (1ULL << 18)) },
            {           
            //"c:maj:7M:#11"
            // x     0 0
            // =========== 
            // | | | | | |
            // | | 2 | | 1 
            // | 3 | | | |
            D({ X, 3, 2, 0, 0, 2 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        {   { Note::C, (TRIAD_MAJ_NO5 | (1ULL << 11) | (1ULL << 9) | (1ULL << 14)) }, 
            {           
            //"c:maj:7M:6:9:no5"                
            // x   0   0 0
            // =========== 
            // | | | | | |
            // | | | 2 | | 
            // | 3 | | | |
            D({ X, 3, 0, 2, 0, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        }

    };

    return db;
}

} // namespace chord::database