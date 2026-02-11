#pragma once

#include <string>
#include <musical/Core/MusicalCoreEnums.h>

namespace musical {

inline std::string to_string(IntervalType type)
{
    switch (type)
    {
        case IntervalType::TONIQUE: return "tonique";
        case IntervalType::SECONDE_MINEURE: return "seconde mineure";
        case IntervalType::SECONDE_MAJEURE: return "seconde majeure";
        case IntervalType::TIERCE_MINEURE: return "tierce mineure";
        case IntervalType::TIERCE_MAJEURE: return "tierce majeure";
        case IntervalType::QUARTE_JUSTE: return "quarte juste";
        case IntervalType::TRITON: return "triton";
        case IntervalType::QUINTE_JUSTE: return "quinte juste";
        case IntervalType::SIXTE_MINEURE: return "sixte mineure";
        case IntervalType::SIXTE_MAJEURE: return "sixte majeure";
        case IntervalType::SEPTIEME_MINEURE: return "septième mineure";
        case IntervalType::SEPTIEME_MAJEURE: return "septième majeure";
        case IntervalType::OCTAVE: return "octave";

        case IntervalType::NEUVIEME_MINEURE: return "neuvième mineure";
        case IntervalType::NEUVIEME_MAJEURE: return "neuvième majeure";
        case IntervalType::DIXIEME_MINEURE: return "dixième mineure";
        case IntervalType::DIXIEME_MAJEURE: return "dixième majeure";
        case IntervalType::ONZIEME: return "onzième";
        case IntervalType::ONZIEME_AUGMENTEE: return "onzième augmentée";
        case IntervalType::DOUZIEME: return "douzième";
        case IntervalType::TREIZIEME_MINEURE: return "treizième mineure";
        case IntervalType::TREIZIEME_MAJEURE: return "treizième majeure";
        case IntervalType::QUATORZIEME_MINEURE: return "quatorzième mineure";
        case IntervalType::QUATORZIEME_MAJEURE: return "quatorzième majeure";
        case IntervalType::DOUBLE_OCTAVE: return "double octave";
    }

    return "inconnu";
}

}
