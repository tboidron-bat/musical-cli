#include <musical/Core/Figure.h>

namespace musical::core
{

unsigned int Figure::duration() const
{
    unsigned int base  = static_cast<uint16_t>(_type);
    unsigned int total = base;

    unsigned int dot_value = base / 2;

    for (uint8_t i = 0; i < static_cast<uint8_t>(_dots); ++i)
    {
        total += dot_value;
        dot_value /= 2;
    }

    return total;
}

}
