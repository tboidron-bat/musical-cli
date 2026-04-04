#include <musical/chord_db/open/maj.h>

namespace chord::db
{

const open_diagram_map& maj_open()
{
    using D = Diagram;
    using F = Diagram::Finger;

    using musical::core::Tone;

    constexpr uint8_t X = D::MUTE;

    static const open_diagram_map db =
    {
        // ========================
        // MAJEUR
        // ========================
        { 
            { Tone::A, TRIAD_MAJ},
            {
            D(
                //"a:maj",                 
                // x 0       0
                // =========== 
                // | | | | | |
                // | | 1 2 3 |
                // | | | | | |
                { X, 0, 2, 2, 2, 0 }, 
                GuitarStandardTuning::A, D::CAGED::A, 
                0,
                { F::INDEX, F::MIDDLE, F::RING }
            )        
            }
        },
        { {Tone::C, TRIAD_MAJ},
            {
            D(
                //"c:maj"
                // x     0   0
                // =========== 
                // | | | | 1 |
                // | | 2 | | |
                // | 3 | | | |
                { X, 3, 2, 0, 1, 0 }, 
                GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::MIDDLE, F::INDEX }
                )
            }
        },
        { {Tone::D, TRIAD_MAJ}, 
            //"d:maj"
            // x x 0 
            // =========== 
            // | | | | | |
            // | | | 1 | 2
            // | | | | 3 |
            {
            D(
                { X, X, 0, 2, 3, 2 }, 
                GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::INDEX, F::RING, F::MIDDLE }
             )
            }
        },
        { {Tone::E, TRIAD_MAJ}, 
            {
            //"e:maj",                 
            // 0       0 0
            // =========== 
            // | | | 1 | |
            // | 2 3 | | |
            // | | | | | |
            D({ 0, 2, 2, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::MIDDLE, F::RING, F::INDEX }
            )
            }
        },
        { {Tone::G, TRIAD_MAJ}, 
            {
            //"g:maj",                 
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | |
            // 2 | | | | 4
            D({ 3, 2, 0, 0, 0, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::MIDDLE, F::INDEX, F::PINKY }
            )   
            }
        },

        // ========================
        // DOMINANT 7
        // ========================

        {  { Tone::A, (TRIAD_MAJ | (1ULL << 10)) },
            
            {
            //"a:maj:7", 
                // x 0   0   0
                // =========== 
                // | | | | | |
                // | | 2 | 3 |
                // | | | | | |
            D({ X, 0, 2, 0, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::MIDDLE, F::RING }
            )       
            }
        },
        {  { Tone::C, ( TRIAD_MAJ | (1ULL << 10)) },
            {
            //"c:maj:7"
            // x         0 
            // =========== 
            // | | | | 1 | 
            // | | 2 | | |
            // | 3 | 4 | |
            D({ X, 3, 2, 3, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::MIDDLE, F::PINKY, F::INDEX }
            )
            }
        },
        { { Tone::D, ( TRIAD_MAJ | (1ULL << 10)) },
            {
            //"d:maj:7"   
            // x x 0
            // =========== 
            // | | | | 1 |
            // | | | 2 | 3
            // | | | | | |
            D({ X, X, 0, 2, 1, 2 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::MIDDLE, F::INDEX, F::RING }
            )
            }
        },
        { { Tone::E, ( TRIAD_MAJ | (1ULL << 10)) },
            //"e:maj:7" 
            // 0   0   0 0
            // =========== 
            // | | | 1 | |
            // | 2 | | | |
            // | | | | | |
            {
            D({ 0, 2, 0, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::MIDDLE, F::INDEX }
            )
            }
        },
        { { Tone::G, ( TRIAD_MAJ | (1ULL << 10)) },
            //"g:maj:7"
            {
            // x   0 0 0
            // =========== 
            // | | | | | 1
            // | 2 | | | |
            // 3 | | | | |
            D({ 3, 2, 0, 0, 0, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::RING, F::MIDDLE, F::INDEX }
            )   
            }
        },


        // ========================
        // MAJ7
        // ========================

        {  { Tone::A, (TRIAD_MAJ | (1ULL << 11)) },
            
            {
                //"a:maj:7M", 
                // x 0       0
                // =========== 
                // | | | 1 | |
                // | | 2 | 3 |
                // | | | | | |
                D({ X, 0, 2, 1, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::MIDDLE, F::INDEX, F::RING }
            )       
            }
        },


        { { Tone::C, (TRIAD_MAJ | (1ULL << 11)) },
            
            {
            //"c:maj:7M"                
            // x     0 0 0 
            // =========== 
            // | | | | | | 
            // | | 2 | | |
            // | 3 | | | |
            D({ X, 3, 2, 0, 0, 0 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::MIDDLE}
            ),
            }
        },
        { { Tone::D, (TRIAD_MAJ | (1ULL << 11)) },
            //"d:maj:7M"
            // x x 0
            // =========== 
            // | | | | | |
            // | | | 1 2 3
            // | | | | | |
            {
            D({ X, X, 0, 2, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D,
                0,
                { F::INDEX, F::MIDDLE, F::RING }
            )   
            }
        },
        { { Tone::E, (TRIAD_MAJ | (1ULL << 11)) },
            //"e:maj:7M"
            // 0       0 0
            // =========== 
            // | | 1 2 | |
            // | 3 | | | |
            // | | | | | |
            {
            D({ 0, 2, 1, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E,
                0,
                { F::RING, F::INDEX, F::MIDDLE }
            )
            }
        },
        { { Tone::G, (TRIAD_MAJ | (1ULL << 11)) },
            {
            //"g:maj:7M"
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | 3
            // 2 | | | | |

            D({ 3, 2, 0, 0, 0, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::MIDDLE, F::INDEX, F::RING }
            )
            }
        },
        // ========================
        // Renversement
        // ========================
        { { Tone::C, TRIAD_MAJ },
            {
            //"c/e                
            // 0     0   0 
            // =========== 
            // | | | | 1 | 
            // | | 2 | | |
            // | 3 | | | |
            D({ 0, 3, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::RING, F::MIDDLE, F::INDEX }
            )   
            }
        },

        // ========================
        // 7ᵇ5
        // ========================
        { { Tone::A, (TRIAD_MAJ_NO5 | (1ULL << 6) | (1ULL << 10) ) },
            {
            //"a:maj:7:b5", 
            // x 0       x
            // ===========
            // | | 1 2 | |
            // | | | | 3 |
            // | | | | | |
            // | | | | | |
            D({ X, 0, 1, 1, 2, X }, GuitarStandardTuning::A, D::CAGED::A,
                0,
                { F::INDEX, F::MIDDLE, F::RING }
            )
            }
        },
        // ========================
        // ▲ᵇ5
        // ========================
        { { Tone::Gs, (TRIAD_MAJ_NO5 | (1ULL << 6) | (1ULL << 11) ) },
            {
            //G#▲ᵇ5/G
            //     0   x x
            // ===========
            // | | | 1 | |
            // | | | | | |
            // 3 4 | | | |
            // | | | | | |
            D({ 3, 3, 0, 1, X, X }, GuitarStandardTuning::G, D::CAGED::G,
                0,
                { F::RING, F::PINKY, F::INDEX }
            )       
            }
        },


        // ========================
        // add11
        // ========================

        { { Tone::D, (TRIAD_MAJ_NO5 | (1ULL << 5)) },
            
            {
            //"d:maj:add4:no5",                 
            //     0 0 x x
            // =========== 
            //      .       
            //      .    
            //      .    
            // | 2 | | | | <-- 9 frette
            // 3 | | | | |
            D({ 10, 9, 0, 0, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G,
                0,
                { F::RING, F::MIDDLE }
             )
            }
        },
        // ========================
        // 
        // ========================

        { { Tone::C, (TRIAD_MAJ | (1ULL << 11) | (1ULL << 18)) },
            {           
            //"c:maj:7M:#11"
            // x     0 0
            // =========== 
            // | | | | | |
            // | | 1 | | 3 
            // | 2 | | | |
            D({ X, 3, 2, 0, 0, 2 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::MIDDLE, F::INDEX, F::RING }
            )
            }
        },
        // ========================
        // 
        // ========================

        {   { Tone::C, (TRIAD_MAJ_NO5 | (1ULL << 11) | (1ULL << 9) | (1ULL << 14)) }, 
            {           
            //"c:maj:7M:6:9:no5"                
            // x   0   0 0
            // =========== 
            // | | | | | |
            // | | | 2 | | 
            // | 3 | | | |
            D({ X, 3, 0, 2, 0, 0 }, GuitarStandardTuning::A, D::CAGED::C,
                0,
                { F::RING, F::MIDDLE }
            )
            }
        }

    };

    return db;
}

} // namespace chord::db
//TODO: ajouter les diagrammes de 7Madd9

            //E shape
            // 0       0 0
            // =========== 
            // | | 1 2 | |
            // | 3 | | | 4
            // | | | | | |

            //C shape ??
            // x   0 0 0 0 
            // =========== 
            // | | | | | | 
            // | | | | | |
            // | 3 | | | |

            //G 
            // x   0   0
            // =========== 
            // | | | | | |
            // | 1 | 2 | 3 
            // 4 | | | | |


