#pragma once

#include <cstdint>

namespace chord::db
{

using IntervalMask = uint64_t;

constexpr IntervalMask TRIAD_MAJ =
    (1ULL << 4) | (1ULL << 7);

constexpr IntervalMask TRIAD_MAJ_NO5 = 
    (1ULL << 4);

constexpr IntervalMask TRIAD_MAJ_B5 =
    (1ULL << 4) | (1ULL << 6);

constexpr IntervalMask MAJ7 = 
    TRIAD_MAJ | (1ULL << 11);

constexpr IntervalMask MAJ7_NO5 = 
    TRIAD_MAJ_NO5 | (1ULL << 11);  

constexpr IntervalMask MAJ7_B5 =
    TRIAD_MAJ_B5 | (1ULL << 11);

constexpr IntervalMask MAJ7_SHARP11 =
    MAJ7 | (1ULL << 18);

constexpr IntervalMask TRIAD_AUG =
    (1ULL << 4) | (1ULL << 8);

constexpr IntervalMask TRIAD_MIN =
    (1ULL << 3) | (1ULL << 7);

constexpr IntervalMask TRIAD_MIN_NO5 =    
    (1ULL << 3);

constexpr IntervalMask DIM_TRIAD =
    (1ULL << 3) | (1ULL << 6);

constexpr IntervalMask SUS2_TRIAD =
    (1ULL << 2) | (1ULL << 7);

constexpr IntervalMask SUS4_TRIAD =
    (1ULL << 5) | (1ULL << 7);

constexpr IntervalMask SUS2_NO5 =
    (1ULL << 2);

constexpr IntervalMask SUS4_NO5 =
    (1ULL << 5);
    
constexpr IntervalMask POWER_CHORD =
    (1ULL << 7);    

}