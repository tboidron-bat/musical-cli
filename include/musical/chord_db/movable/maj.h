#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

namespace chord::db
{

    constexpr uint64_t TRIAD_MAJ = (1ULL<<4) | (1ULL<<7);
    constexpr uint64_t TRIAD_MAJ_NO5 = TRIAD_MAJ & ~(1ULL<<7);    

    using IntervalMask = uint64_t; 
    const std::unordered_map<IntervalMask,std::vector<Diagram>>
    & maj_movable();

} //chord::db