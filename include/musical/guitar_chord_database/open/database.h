#pragma once

#include <map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{
    using IntervalMask = uint64_t;

    enum class NoteEnum : uint8_t
    {
        C=0, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B
    };

    //using key_t = std::pair<Note, IntervalMask>;??

    struct key_t
    {        
        NoteEnum _root; 
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

} // namespace chord::database