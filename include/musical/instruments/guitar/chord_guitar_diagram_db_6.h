#pragma once

#include <unordered_map>
#include <vector>

#include <musical/instruments/guitar/chord_guitar_diagram.h>

namespace musical::chord::guitar {

/*

    - indexée par :
        * musical::instruments::guitar::TuningType
        * formule d’accord (intervalles en demi-tons depuis la fondamentale)
    - contient :
        * toutes les positions connues pour un accord donné
*/

template <>
const std::unordered_map<
    musical::instrument::guitar::TuningType,
    std::unordered_map<
        musical::chord::chord_intervals,
        std::vector<Diagram<6>>,
        musical::chord::IntervalVectorHash
    >
>&
database<6>();

} // namespace musical::chord::guitar
