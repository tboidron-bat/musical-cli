#include <musical/core/chord/ChordType.h>

#include <bit>

namespace musical::core::chord
{
ChordType::IntervalMask 
ChordType::make(const std::vector<Interval>& v)
{
    IntervalMask mask = 0;
    for (auto i : v)
        mask |= make(i);
    return mask;
}
ChordType::IntervalMask
ChordType::make(std::initializer_list<Interval> list)
{
    IntervalMask mask = 0;
    for (auto i : list)
        mask |= make(i);
    return mask;
}
ChordType::ChordType(std::initializer_list<Interval> list)
{
    for (auto i : list)
        _intervals_mask |= make(i);
}    
ChordType& ChordType::operator += (Interval i) noexcept
{
    _intervals_mask |= make(i);
    return *this;        
}
ChordType& ChordType::operator -= (Interval i) noexcept
{
    _intervals_mask &= ~make(i);
    return *this;            
}
bool ChordType::operator==(const ChordType& other) const
{
    return _intervals_mask == other._intervals_mask;
}    
bool ChordType::has(Interval i) const noexcept
{
    return (_intervals_mask & make(i)) != 0;
}
bool ChordType::has(uint64_t mask) const noexcept
{
    return (_intervals_mask & mask) == mask;
}
std::size_t ChordType::size() const
{
    return std::popcount(_intervals_mask);        
}    
bool ChordType::empty() const noexcept
{
    return _intervals_mask == 0;
}
void ChordType::clear() noexcept
{
    _intervals_mask = 0;
}
}    