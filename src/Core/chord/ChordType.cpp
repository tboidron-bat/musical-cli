#include <musical/Core/chord/ChordType.h>

#include <musical/analysis/chord/io.h>
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
std::ostream& operator<<(std::ostream& os, const ChordType& chord_type)
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