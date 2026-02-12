#pragma once

#include <string>
#include <musical/Core/intervals_defs.h>

namespace musical {

inline std::string to_string(core::IntervalType type)
{
    switch (type)
    {
        case core::IntervalType::TONIQUE: return "tonique";
        case core::IntervalType::SECONDE_MINEURE: return "seconde mineure";
        case core::IntervalType::SECONDE_MAJEURE: return "seconde majeure";
        case core::IntervalType::TIERCE_MINEURE: return "tierce mineure";
        case core::IntervalType::TIERCE_MAJEURE: return "tierce majeure";
        case core::IntervalType::QUARTE_JUSTE: return "quarte juste";
        case core::IntervalType::TRITON: return "triton";
        case core::IntervalType::QUINTE_JUSTE: return "quinte juste";
        case core::IntervalType::SIXTE_MINEURE: return "sixte mineure";
        case core::IntervalType::SIXTE_MAJEURE: return "sixte majeure";
        case core::IntervalType::SEPTIEME_MINEURE: return "septième mineure";
        case core::IntervalType::SEPTIEME_MAJEURE: return "septième majeure";
        case core::IntervalType::OCTAVE: return "octave";

        case core::IntervalType::NEUVIEME_MINEURE: return "neuvième mineure";
        case core::IntervalType::NEUVIEME_MAJEURE: return "neuvième majeure";
        case core::IntervalType::DIXIEME_MINEURE: return "dixième mineure";
        case core::IntervalType::DIXIEME_MAJEURE: return "dixième majeure";
        case core::IntervalType::ONZIEME: return "onzième";
        case core::IntervalType::ONZIEME_AUGMENTEE: return "onzième augmentée";
        case core::IntervalType::DOUZIEME: return "douzième";
        case core::IntervalType::TREIZIEME_MINEURE: return "treizième mineure";
        case core::IntervalType::TREIZIEME_MAJEURE: return "treizième majeure";
        case core::IntervalType::QUATORZIEME_MINEURE: return "quatorzième mineure";
        case core::IntervalType::QUATORZIEME_MAJEURE: return "quatorzième majeure";
        case core::IntervalType::DOUBLE_OCTAVE: return "double octave";
    }

    return "inconnu";
}

}
