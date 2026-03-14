#pragma once

#include <musical/guitar_chord_database/OpenChordDiagram.h>
#include <musical/Core/intervals_defs.h>

namespace chord::database
{

inline const DiagramMap& database_maj7b5()
{
    using D  = OpenChordDiagram;
    using S  = D::string_state;
    using SH = D::CAGEDShape;
    using ROOT = D::GuitarString;
    using CT = musical::core::chord::ChordType;
    using IT = musical::core::IntervalType;

    static const DiagramMap db =
    {
        { CT({ IT::TIERCE_MAJEURE, IT::QUINTE_DIMINUEE, IT::SEPTIEME_MAJEURE }), {

        // =================================================
        // maj7b5 – basse corde A (forme type A déplacée)
        //
        // x 0 2 1 2 0
        // =================
        // | | | | | |
        // | | 2 | 3 |
        // | | | 1 | |
        // | | | | | |
        //
        // fondamentale sur corde A
        // =================================================
        D{{
            S::muted(),
            S::open_string(),
            S::fretted(2,2),
            S::fretted(1,1),
            S::fretted(2,3),
            S::open_string()
        }, ROOT::A, SH::A},

        // =================================================
        // maj7b5 – basse corde E (forme type E)
        //
        // 1 x 2 2 1 x
        // =================
        // |1| | | | | |
        // | | |2|3| | |
        // | | | | | | |
        // | | | | | | |
        //
        // fondamentale sur corde LOW_E
        // =================================================
        D{{
            S::fretted(1,1),
            S::muted(),
            S::fretted(2,3),
            S::fretted(2,4),
            S::fretted(1,2),
            S::muted()
        }, ROOT::LOW_E, SH::E},

        // =================================================
        // maj7b5 – voicing compact jazz (4 cordes)
        //
        // x x 2 1 2 1
        // ===========
        // | | | | | |
        // | | | | | |
        // | |2| |4|2|
        // | | |1| | |
        //
        // fondamentale sur corde D
        // =================================================
        D{{
            S::muted(),
            S::muted(),
            S::fretted(2,3),
            S::fretted(1,1),
            S::fretted(2,4),
            S::fretted(1,2)
        }, ROOT::D, SH::D},

        // =================================================
        // maj7b5 – renversement (tierce à la basse)
        //
        // x x 1 1 2 2
        // ===========
        // | | | | | |
        // | | | | | |
        // | |1|1| | |
        // | | | |2|2|
        //
        // fondamentale interne (renversement)
        // =================================================
        D{{
            S::muted(),
            S::muted(),
            S::fretted(1,1),
            S::fretted(1,2),
            S::fretted(2,3),
            S::fretted(2,4)
        }, ROOT::D, SH::D}

        }}
    };

    return db;
}

} // namespace chord::database