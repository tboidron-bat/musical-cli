#include <musical/guitar_chord_database/database_open_a.h>
#include <musical/Core/intervals_defs.h>

namespace chord::database
{
const DiagramMap& database_open_a()
{
    using D  = OpenChordDiagram;
    using S  = D::string_state;
    using SHAPE = D::CAGEDShape;
    using CT = musical::core::chord::ChordType;
    using IT = musical::core::IntervalType;

    static const DiagramMap db =
    {
        // =================================================
        // A MAJEUR (forme A)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,1),
                S::fretted(2,2),
                S::fretted(2,3),
                S::open_string()
            }, D::GuitarString::A, SHAPE::A}
        }},

        // =================================================
        // A MINEUR 
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::fretted(2,3),
                S::fretted(1,1),
                S::open_string()
            }, D::GuitarString::A, SHAPE::A}
        }},

        // =================================================
        // A DOMINANTE 7 
        // x 0   0   0 
        // ===========
        // | | | | | | 
        // | | 2 | 3 | 
        // | | | | | | 
        // | | | | | | 
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(2,3),
                S::open_string()
            }, D::GuitarString::A, SHAPE::A}
        }},

        // =================================================
        // Am7
        // x 0   0   0 
        // ===========
        // | | | | 1 | 
        // | | 2 | | | 
        // | | | | | | 
        // | | | | | | 
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(1,1),
                S::open_string()
            }, D::GuitarString::A, SHAPE::A}
        }}
    };

    return db;
}

} // namespace chord::database