#pragma once

#include <ostream>

#include <musical/core/chord/ChordType.h>

#include <musical/io/core/IntervalsIO.h>

#include <bit>

namespace musical::core::chord {

inline std::ostream& operator<<(std::ostream& os, const ChordType& chord_type)
{
    using musical::core::Interval;
    using musical::core::to_symbol;

    uint64_t mask = chord_type.intervals_mask();

    os << "{ ";

    bool first = true;

    while (mask)
    {
        uint8_t i = std::countr_zero(mask);

        if (!first)
            os << ' ';

        os << to_symbol(static_cast<Interval>(i));

        mask &= (mask - 1); // clear lowest bit
        first = false;
    }

    os << " }";

    return os;
}
}