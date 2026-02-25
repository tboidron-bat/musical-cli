#include <musical/instruments/guitar/six_strings/database_shape_c.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_shape_c()
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
        // MAJEUR (forme C)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            // C
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(1,1),
                S::open_string()
            }, ROOT::A, SHAPE::C}
        }},

        // =================================================
        // MINEUR (forme C partielle)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            // Cm (version partielle typique)
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(1,1),
                S::open_string(),
                S::fretted(1,1),
                S::muted()
            }, ROOT::A, SHAPE::C}
        }},

        // =================================================
        // DOMINANTE 7 (forme C)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // C7
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(2,2),
                S::fretted(3,4),
                S::fretted(1,1),
                S::open_string()
            }, ROOT::A, SHAPE::C}
        }},

        // =================================================
        // MAJ7 (forme C)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }), {

            // Cmaj7
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(2,2),
                S::open_string(),
                S::open_string(),
                S::open_string()
            }, ROOT::A, SHAPE::C}
        }},

        // =================================================
        // m7 (forme C)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // Cm7 (version partielle typique)
            D{{ 
                S::muted(),
                S::fretted(3,3),
                S::fretted(1,1),
                S::fretted(3,4),
                S::fretted(1,1),
                S::muted()
            }, ROOT::A, SHAPE::C}
        }}
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings