#include <musical/guitar_chord_database/data_open.h>

namespace chord::database
{

const diagram_map& database_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const diagram_map db =
    {
        // ========================
        // MAJEUR
        // ========================

        { "a:maj", {
            D({ X, 0, 2, 2, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            // x     0   0
            // =========== 
            // | | | | 1 |
            // | | 2 | | |
            // | 3 | | | |
        }},
        { "c:maj", {
            D({ X, 3, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
        }},
        { "d:maj", {
            D({ X, X, 0, 2, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D),
        }},
        { "e:maj", {
            D({ 0, 2, 2, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | |
            // 2 | | | | 4
        }},
        { "g:maj", {
            D({ 3, 2, 0, 0, 0, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},

        // ========================
        // MINEUR
        // ========================

        { "a:min", 
            {
            D({ X, 0, 2, 2, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { "c:min", 
            {
             // x     0   x 
            // =========== 
            // | | 1 | 1 | 
            // | | | | | |
            // | 3 | | | 3 
            D({ X, 3, 1, 0, 1, X }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { "d:min", 
            {
            D({ X, X, 0, 2, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { "e:min", 
            {
            D({ 0, 2, 2, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            
            }
        },
        { "g:min", 
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
        // DOMINANT 7
        // ========================

        { "a:maj:7", 
            {
            D({ X, 0, 2, 0, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { "c:maj:7", 
            {
            // x         0 
            // =========== 
            // | | | | 1 | 
            // | | 2 | | |
            // | 3 | 3 | |
            D({ X, 3, 2, 3, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { "d:maj:7", 
            {
            D({ X, X, 0, 2, 1, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { "e:maj:7", 
            {
            D({ 0, 2, 0, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { "g:maj:7", 
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
        // MIN7
        // ========================

        { "a:min:7", 
            {
            D({ X, 0, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { "d:min:7", 
            {
            D({ X, X, 0, 2, 1, 1 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { "e:min:7", 
            {
            D({ 0, 2, 0, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { "g:min:7", 
            {
            //     0 0 
            // =========== 
            // | 1 | | | 2
            // | | | | | |
            // 3 | | | 4 |

            D({ 3, 1, 0, 0, 3, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },

        // ========================
        // MAJ7
        // ========================

        { "c:maj:7M", 
            {
            // CMAJ7 
            // x     0 0 0 
            // =========== 
            // | | | | | | 
            // | | 2 | | |
            // | 3 | | | |
            D({ X, 3, 2, 0, 0, 0 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { "d:maj:7M", 
            {
            D({ X, X, 0, 2, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            }
        },
        { "e:maj:7M", 
            {
            D({ 0, 2, 1, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            }
        },
        { "g:maj:7M", 
            {
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

        { "a:7:b5", 
            {
            // x 0       x
            // ===========
            // | | 1 2 | |
            // | | | | 3 |
            // | | | | | |
            // | | | | | |
            D({ X, 0, 1, 1, 2, X }, GuitarStandardTuning::A, D::CAGED::A),
            }
        },
        { "d:add4:no5", 
            {
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
        { "e:7:sus4", 
            {           
            //0       0 x 
            // =========== 
            //      .       
            //      .    
            //      .    
            // | 1 2 3 | | <-- VII fr.
            // | | | | | |
            D({ 0, 7, 7, 7, 0, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),
            }
        },
        { "c:7M:#11", 
            {           
            // x     0 0
            // =========== 
            // | | | | | |
            // | | 2 | | 1 
            // | 3 | | | |
            D({ X, 3, 2, 0, 0, 2 }, GuitarStandardTuning::A, D::CAGED::C),
            }
        },
        { "c:7M:6:9:no5", 
            {           
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