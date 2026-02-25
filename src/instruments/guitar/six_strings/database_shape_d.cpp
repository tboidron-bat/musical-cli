#include <musical/instruments/guitar/six_strings/database_shape_d.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_shape_d()
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
        // MAJEUR (forme D)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            // D
            D{{ 
                S::muted(),
                S::muted(),
                S::open_string(),
                S::fretted(2,1),
                S::fretted(3,3),
                S::fretted(2,2)
            }, ROOT::D, SHAPE::D}
        }},

        // =================================================
        // MINEUR (forme D)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            // Dm
            D{{ 
                S::muted(),
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::fretted(3,3),
                S::fretted(1,1)
            }, ROOT::D, SHAPE::D}
        }},

        // =================================================
        // DOMINANTE 7 (forme D)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // D7
            D{{ 
                S::muted(),
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::fretted(1,1),
                S::fretted(2,3)
            }, ROOT::D, SHAPE::D}
        }},

        // =================================================
        // m7 (forme D)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // Dm7
            D{{ 
                S::muted(),
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::fretted(1,1),
                S::fretted(1,1)
            }, ROOT::D, SHAPE::D}
        }},

        // =================================================
        // MAJ7 (forme D)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }), {

            // Dmaj7
            D{{ 
                S::muted(),
                S::muted(),
                S::open_string(),
                S::fretted(2,2),
                S::fretted(2,3),
                S::fretted(2,4)
            }, ROOT::D, SHAPE::D}
        }}
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings