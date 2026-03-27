#include <musical/Core/chord/Chord.h>

namespace musical::core::chord {

std::size_t Chord::size() const
{
    return 1 + _type.size();
}
std::vector<Pitch> 
Chord::notes() const
{
    std::vector<Pitch> result;

    result.push_back(_root);    

    uint8_t root_value = _root.value();
    uint64_t mask = _type.intervals_mask();

    for (uint8_t i = 0; i < 64; ++i)
    {
        if (!(mask & (1ULL << i)))
            continue;

        uint8_t value = static_cast<uint8_t>(root_value + i);
        result.emplace_back(value);
    }
    return result;
}
std::ostream& operator<<(std::ostream& os, const Chord& chord)
{
    os << chord.root()
       << " "
       << chord.type();

    return os;
}

} // namespace musical::core::chord