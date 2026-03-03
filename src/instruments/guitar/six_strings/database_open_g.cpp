#include <musical/instruments/guitar/six_strings/database_open_g.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_open_g()
{
    using D  = OpenChordDiagram;
    using S  = D::string_state;
    using SHAPE = D::CAGEDShape;
    using ROOT  = D::GuitarString;
    using CT = musical::core::chord::ChordType;
    using IT = musical::core::IntervalType;

    static const DiagramMap db =
    {
        // =========================================================
        // MAJEUR 
        // x   0 0 0
        // =========== 
        // | | | | | |
        // | 1 | | | |
        // 2 | | | | 4
        // =========================================================

        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            // G
            D{{ 
                S::fretted(3,2),
                S::fretted(2,1),
                S::open_string(),
                S::open_string(),
                S::open_string(),
                S::fretted(3,4)
            }, ROOT::LOW_E, SHAPE::G}
        }},

        // =========================================================
        //
        // MINEUR 
        // x   0 0 0
        // =========== 
        // | 1 | | | |
        // | | | | | |
        // 2 | | | 3 4
        //
        // =========================================================


        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::fretted(3,2),
                S::fretted(1,1),
                S::open_string(),   
                S::open_string(),
                S::fretted(3,3),
                S::fretted(3,4)
            },  ROOT::LOW_E, 
                SHAPE::G,
                static_cast<uint16_t>(SixStringDiagram::Style::CLASSICAL)
            }
        }},
        // =========================================================
        //
        // DOMINANTE 7
        // x   0 0 0
        // =========== 
        // | | | | | 1
        // | 2 | | | |
        // 3 | | | | |
        //
        // =========================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            D{{ 
                S::fretted(3,3),
                S::fretted(2,2),
                S::open_string(),
                S::open_string(),
                S::open_string(),
                S::fretted(1,1)
            },  ROOT::LOW_E, 
                SHAPE::G,
                static_cast<uint16_t>(SixStringDiagram::Style::BLUES) |
                static_cast<uint16_t>(SixStringDiagram::Style::JAZZ)}
        }},

        // =================================================
        // MAJ7 
        //     0 0 0
        // =========== 
        // | | | | | |
        // | 1 | | | 3
        // 2 | | | | |

        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }), {

            D{{ 
                S::fretted(3,2),
                S::fretted(2,1),
                S::open_string(),
                S::open_string(),
                S::open_string(),
                S::fretted(2,3)
            }, ROOT::LOW_E, SHAPE::G}
        }},

        // =================================================
        // Gm7 
        //     0 0 
        // =========== 
        // | 1 | | | 2
        // | | | | | |
        // 3 | | | 4 |

        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            D{{ 
                S::fretted(3,3),
                S::fretted(1,1),
                S::open_string(),
                S::open_string(),
                S::fretted(3,4),
                S::fretted(1,2)
            },  ROOT::LOW_E, 
                SHAPE::G,
                static_cast<uint16_t>(SixStringDiagram::Style::AMBIENT) }
        }},
        // =========================================================
        // Dadd4(no5) (voicing ouvert atmosphérique)
        //
        //     0 0 x x
        // =========== 
        //      .       
        //      .    
        //      .    
        // | 1 | | | | <-- 9 frette
        // 2 | | | | |
        //
        // =========================================================

        {
            CT({ IT::TIERCE_MAJEURE, IT::QUARTE_JUSTE }), 
            {

                D{{
                    S::fretted(10, 2),  
                    S::fretted(9,  1),  
                    S::open_string(),   
                    S::open_string(),   
                    S::muted(),         
                    S::muted()          
                },
                ROOT::LOW_E,
                SHAPE::G,
                static_cast<uint16_t>(SixStringDiagram::Style::PINKFLOYDIAN) 
                }
            }
        }        
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings