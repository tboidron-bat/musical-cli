#include <musical/instruments/guitar/six_strings/database_shape_a.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_shape_a()
{
    using D  = ChordDiagram;
    using S  = D::string_state;
    using SHAPE = D::CAGEDShape;
    using ROOT  = D::GuitarString;
    using CT = musical::core::chord::ChordType;
    using IT = musical::core::IntervalType;

    static const DiagramMap db =
    {
        // =================================================
        // MAJEUR (forme A)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,1),
                S::fretted(2,2),
                S::fretted(2,3),
                S::open_string()
            }, ROOT::A, SHAPE::A}
        }},

        // =================================================
        // MINEUR (forme A)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::fretted(2,3),
                S::fretted(1,1),
                S::open_string()
            }, ROOT::A, SHAPE::A}
        }},

        // =================================================
        // DOMINANTE 7 (forme A)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(2,3),
                S::open_string()
            }, ROOT::A, SHAPE::A}
        }},

        // =================================================
        // m7 (forme A)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            D{{ 
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(1,1),
                S::open_string()
            }, ROOT::A, SHAPE::A}
        }}
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings