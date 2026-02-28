#include <musical/instruments/guitar/six_strings/database_open_e.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_open_e()
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
        // MAJEUR (forme E)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }), {

            // E
            D{{ 
                S::open_string(),
                S::fretted(2,2),
                S::fretted(2,3),
                S::fretted(1,1),
                S::open_string(),
                S::open_string()
            }, ROOT::LOW_E, SHAPE::E}
        }},

        // =================================================
        // MINEUR (forme E)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }), {

            // Em
            D{{ 
                S::open_string(),
                S::fretted(2,2),
                S::fretted(2,3),
                S::open_string(),
                S::open_string(),
                S::open_string()
            }, ROOT::LOW_E, SHAPE::E}
        }},

        // =================================================
        // DOMINANTE 7 (forme E)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // E7
            D{{ 
                S::open_string(),
                S::fretted(2,2),
                S::open_string(),
                S::fretted(1,1),
                S::open_string(),
                S::open_string()
            }, ROOT::LOW_E, SHAPE::E}
        }},

        // =================================================
        // MAJ7 (forme E)
        // =================================================
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }), {

            // Emaj7
            D{{ 
                S::open_string(),
                S::fretted(2,3),
                S::fretted(1,1),
                S::fretted(1,2),
                S::open_string(),
                S::open_string()
            }, ROOT::LOW_E, SHAPE::E}
        }},

        // =================================================
        // m7 (forme E)
        // =================================================
        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {

            // Em7
            D{{ 
                S::open_string(),
                S::fretted(2,2),
                S::open_string(),
                S::open_string(),
                S::open_string(),
                S::open_string()
            }, ROOT::LOW_E, SHAPE::E}
        }}
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings