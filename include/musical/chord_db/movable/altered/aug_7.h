#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/triads.h>

namespace chord::db
{
    const std::unordered_map<IntervalMask, std::vector<Diagram>>&
    aug_7_movable();
} 

