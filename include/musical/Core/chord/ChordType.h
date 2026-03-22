#pragma once

#include <cstdint>
#include <vector>

#include <musical/Core/Intervals.h>




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
private:
    using IntervalMask = uint64_t; 

    IntervalMask _intervals_mask {0};
   
public:
    constexpr ChordType() = default;

    constexpr explicit ChordType(IntervalMask intervals_mask)
        : _intervals_mask(intervals_mask)
    {}

    constexpr ChordType(std::initializer_list<Interval> list);

public:
    constexpr ChordType& operator += (Interval) noexcept;
    constexpr ChordType& operator -= (Interval) noexcept;    

    constexpr bool operator==(const ChordType& other) const;

    IntervalMask intervals_mask() const noexcept { return _intervals_mask; }    

    constexpr bool empty() const noexcept;
    constexpr bool has(Interval) const noexcept;
    constexpr bool has(uint64_t) const noexcept;

    constexpr std::size_t size() const;    
    constexpr void clear() noexcept;       

public:
    static constexpr IntervalMask make(Interval);    
    static constexpr IntervalMask make(std::initializer_list<Interval>);            
    static IntervalMask make(const std::vector<Interval>&);    

};

} 
