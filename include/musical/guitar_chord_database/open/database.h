#pragma once

#include <map>
#include <vector>
#include <cstdint>

#include <musical/guitar_chord_database/Diagram.h>

namespace chord::database
{
    constexpr uint64_t TRIAD_MAJ = (1ULL<<4) | (1ULL<<7);
    constexpr uint64_t TRIAD_MAJ_NO5 = TRIAD_MAJ & ~(1ULL<<7);    

    using IntervalMask = uint64_t;

    enum class Note : uint8_t
    {
        C=0, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B
    };

    struct key_t
    {        
        Note _root; 
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