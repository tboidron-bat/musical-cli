#include <musical/Core/chord/ChordType.h>

namespace musical::core::chord
{
    std::size_t ChordType::size() const
    {
        return _intervals.size();
    }    
    ChordClassType ChordType::class_type() const
    {
        // +1 car la tonique n'est pas stockée dans _intervals
        switch (size() + 1)
        {
            case 2: return ChordClassType::DYAD;
            case 3: return ChordClassType::TRIAD;
            case 4: return ChordClassType::TETRAD;
            case 5: return ChordClassType::PENTAD;
            case 6: return ChordClassType::HEXAD;
            default: return ChordClassType::UNKNOWN;
        }
    } 
}    