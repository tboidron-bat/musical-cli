#include <musical/instruments/guitar/chord_guitar_diagram_db_6.h>

namespace musical::chord::guitar {

template <>
const std::unordered_map<
    musical::instrument::guitar::TuningType,
    std::unordered_map<
        musical::chord::chord_intervals,
        std::vector<Diagram<6>>,
        musical::chord::IntervalVectorHash
    >
>&
database<6>()
{
    using D  = Diagram<6>;
    using S  = D::string_state;
    using IT = musical::core::IntervalType;

    static const std::unordered_map<
        musical::instrument::guitar::TuningType,
        std::unordered_map<
            musical::chord::chord_intervals,
            std::vector<D>,
            musical::chord::IntervalVectorHash
        >
    > db =
    {
        {
            musical::instrument::guitar::TuningType::STANDARD,
            {

                // =================================================
                // MAJEUR
                // =================================================
                { { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }, {

                    D{ 0, {{{0,0},{2,2},{2,3},{1,1},{0,0},{0,0}}}}, // E
                    D{ 0, {{{S::MUTED,0},{0,0},{2,1},{2,2},{2,3},{0,0}}}}, // A
                    D{ 0, {{{S::MUTED,0},{S::MUTED,0},{0,0},{2,1},{3,3},{2,2}}}}, // D
                    D{ 0, {{{S::MUTED,0},{3,3},{2,2},{0,0},{1,1},{0,0}}}}, // C
                    D{ 0, {{{3,2},{2,1},{0,0},{0,0},{0,0},{3,3}}}}  // G
                }},

                // =================================================
                // MINEUR
                // =================================================
                { { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }, {

                    D{ 0, {{{0,0},{2,2},{2,3},{0,0},{0,0},{0,0}}}}, // Em
                    D{ 0, {{{S::MUTED,0},{0,0},{2,2},{2,3},{1,1},{0,0}}}}, // Am
                    D{ 0, {{{S::MUTED,0},{S::MUTED,0},{0,0},{2,2},{3,3},{1,1}}}} // Dm
                }},

                // =================================================
                // DOMINANTE 7
                // =================================================
                { { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }, {

                    D{ 0, {{{0,0},{2,2},{0,0},{1,1},{0,0},{0,0}}}}, // E7
                    D{ 0, {{{S::MUTED,0},{0,0},{2,2},{0,0},{2,3},{0,0}}}}, // A7
                    D{ 0, {{{S::MUTED,0},{S::MUTED,0},{0,0},{2,2},{1,1},{2,3}}}} // D7
                }},

                // =================================================
                // MAJ7
                // =================================================
                { { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE }, {

                    D{ 0, {{{0,0},{2,3},{1,1},{1,2},{0,0},{0,0}}}}, // Emaj7
                    D{ 0, {{{S::MUTED,0},{3,3},{2,2},{0,0},{0,0},{0,0}}}} // Cmaj7
                }},

                // =================================================
                // m7
                // =================================================
                { { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }, {

                    D{ 0, {{{0,0},{2,2},{0,0},{0,0},{0,0},{0,0}}}}, // Em7
                    D{ 0, {{{S::MUTED,0},{0,0},{2,2},{0,0},{1,1},{0,0}}}} // Am7
                }},

                // =================================================
                // SUS2
                // =================================================
                { { IT::SECONDE_MAJEURE, IT::QUINTE_JUSTE }, {

                    D{ 0, {{{S::MUTED,0},{S::MUTED,0},{0,0},{2,2},{3,3},{0,0}}}}
                }},

                // =================================================
                // SUS4
                // =================================================
                { { IT::QUARTE_JUSTE, IT::QUINTE_JUSTE }, {

                    D{ 0, {{{S::MUTED,0},{0,0},{2,2},{2,3},{3,4},{0,0}}}}
                }},

                // =================================================
                // DIMINUÉ
                // =================================================
                { { IT::TIERCE_MINEURE, IT::TRITON }, {

                    D{ 0, {{{S::MUTED,0},{2,2},{3,3},{2,1},{3,4},{S::MUTED,0}}}}
                }},

                // =================================================
                // AUGMENTÉ
                // =================================================
                { { IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE }, {

                    D{ 0, {{{0,0},{3,3},{2,2},{1,1},{1,1},{0,0}}}}
                }}

            }
        }
    };

    return db;
}

} // namespace musical::chord::guitar
