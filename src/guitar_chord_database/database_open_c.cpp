#include <musical/guitar_chord_database/database_open_c.h>
#include <musical/Core/intervals_defs.h>

namespace chord::database
{
const DiagramMap& database_open_c()
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
        // C majeure
        // x     0   0
        // =========== 
        // | | | | 1 |
        // | | 2 | | |
        // | 3 | | | |
        // =========================================================

        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(1,1),
                S::open_string()
            }, 
            ROOT::A, 
            SHAPE::C,
            static_cast<uint16_t>(SixStringDiagram::Style::CLASSICAL)
        }
        }},

        // =========================================================
        // C mineure
        // x     0   x 
        // =========== 
        // | | 1 | 1 | 
        // | | | | | |
        // | 3 | | | 3 
        //   
        // =========================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(1,1),
                S::open_string(),
                S::fretted(1,1),
                S::muted()
            }, 
            ROOT::A, 
            SHAPE::C,
            static_cast<uint16_t>(SixStringDiagram::Style::CLASSICAL)
            }
        }},

        // =========================================================
        // C DOMINANTE 7
        // x         0 
        // =========== 
        // | | | | 1 | 
        // | | 2 | | |
        // | 3 | 3 | |
        //
        // =========================================================

        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // C7
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(2,2),
                S::fretted(3,4),
                S::fretted(1,1),
                S::open_string()
            }, 
            ROOT::A, 
            SHAPE::C,
            static_cast<uint16_t>(SixStringDiagram::Style::BLUES) |
            static_cast<uint16_t>(SixStringDiagram::Style::JAZZ)
            }
         }},    

        // =========================================================
        // CMAJ7 
        // x     0 0 0 
        // =========== 
        // | | | | | | 
        // | | 2 | | |
        // | 3 | | | |
        //
        // =========================================================

        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }), {

            // Cmaj7
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(2,2),
                S::open_string(),
                S::open_string(),
                S::open_string()
            }, 
            ROOT::A, 
            SHAPE::C,
            static_cast<uint16_t>(SixStringDiagram::Style::BLUES) |
            static_cast<uint16_t>(SixStringDiagram::Style::JAZZ) |
            static_cast<uint16_t>(SixStringDiagram::Style::FUNK)}
        }},

    };

    return db;
}

} // namespace chord::database