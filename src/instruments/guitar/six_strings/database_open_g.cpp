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
        // =================================================
        // MAJEUR (forme G)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            // G
            D{{ 
                S::fretted(3,2),
                S::fretted(2,1),
                S::open_string(),
                S::open_string(),
                S::open_string(),
                S::fretted(3,3)
            }, ROOT::LOW_E, SHAPE::G}
        }},

        // =================================================
        // MINEUR (forme G partielle)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            // Gm (version partielle)
            D{{ 
                S::fretted(3,3),
                S::fretted(5,4),
                S::fretted(5,4),
                S::fretted(3,1),
                S::muted(),
                S::muted()
            }, ROOT::LOW_E, SHAPE::G}
        }},

        // =================================================
        // DOMINANTE 7 (forme G)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // G7
            D{{ 
                S::fretted(3,2),
                S::fretted(2,1),
                S::open_string(),
                S::open_string(),
                S::open_string(),
                S::fretted(1,1)
            }, ROOT::LOW_E, SHAPE::G}
        }},

        // =================================================
        // MAJ7 (forme G)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }), {

            // Gmaj7
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
        // m7 (forme G)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // Gm7 (version partielle)
            D{{ 
                S::fretted(3,3),
                S::fretted(5,4),
                S::fretted(3,1),
                S::fretted(3,1),
                S::muted(),
                S::muted()
            }, ROOT::LOW_E, SHAPE::G}
        }}
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings