#pragma once

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{

inline const diagram_map& database_maj7b5()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;
    constexpr uint8_t O = 0;

    static const diagram_map db =
    {
        { "7Mb5", {

        // maj7b5 – basse corde E (forme type E)

        // 1 x 2 2 1 x
        // =============
        // 1 | | | 1 | |
        // | | 2 3 | | |
        // | | | | | | |
        // | | | | | | |
        //
        // fondamentale sur corde LOW_E
        // =================================================
        D({ 1, X, 2, 2, 1, X }, 0, D::CAGED::E),

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
        D({ X, X, 2, 1, 2, 1 }, 2, D::CAGED::D),

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
        D({ X, X, 1, 1, 2, 2 }, 2, D::CAGED::D)

        }}
    };

    return db;
}

} // namespace chord::database