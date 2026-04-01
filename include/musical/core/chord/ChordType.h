#pragma once

#include <cstdint>
#include <vector>
#include <assert.h>

#include <musical/core/Intervals.h>

namespace musical::core::chord {
 
/**
 *
 * Exemple :
 *   ChordType m7 = ChordType({
 *    Interval::MINOR_THIRD,
 *    Interval::PERFECT_FIFTH,
 *    Interval::MINOR_SEVENTH
 *    });    
 * 
 * La tonique appartient à la classe Chord.
 */
class ChordType
{
public:
    using IntervalMask = uint64_t;         
private:

    IntervalMask _intervals_mask {0};
   
public:
    ChordType() = default;

    explicit ChordType(IntervalMask intervals_mask)
        : _intervals_mask(intervals_mask)
    {}

    ChordType(std::initializer_list<Interval> list);

public:
    ChordType& operator += (Interval) noexcept;
    ChordType& operator -= (Interval) noexcept;    
    bool operator==(const ChordType& other) const;

    IntervalMask intervals_mask() const noexcept { return _intervals_mask; }    

    bool empty() const noexcept;
    bool has(Interval) const noexcept;
    bool has(uint64_t) const noexcept;
    std::size_t size() const;    
    void clear() noexcept;       

public:
    static IntervalMask make(Interval i)
    {
        // Option safe (debug)
        assert(i != Interval::ROOT);

        return 1ULL << static_cast<uint8_t>(i);
    }
    static IntervalMask make(std::initializer_list<Interval>);            
    static IntervalMask make(const std::vector<Interval>&);    

};
} 
