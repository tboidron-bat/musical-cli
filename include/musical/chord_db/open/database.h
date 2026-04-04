#pragma once

#include <map>
#include <vector>
#include <cstdint>

#include <musical/chord_db/Diagram.h>

#include <musical/core/Tone.h>
#include <musical/core/chord/ChordType.h>

namespace chord::db
{
    using IntervalMask = musical::core::chord::ChordType::IntervalMask;

    struct key_t
    {        
        musical::core::Tone _root; 
        IntervalMask _mask;

        bool operator==(const key_t& other) const noexcept
        {
            return _root == other._root && _mask == other._mask;
        }   
        bool operator<(const key_t& other) const noexcept
        {
            if (_root != other._root)
                return _root < other._root;

            return _mask < other._mask;
        }             
    };

    using open_diagram_map = std::map<key_t, std::vector<Diagram>>;

    // ------------------------------------------------------------
    // Global OPEN DB
    // ------------------------------------------------------------
    const open_diagram_map&data_open();

} // namespace chord::db