#pragma once

#include <cstdint>
#include <string>

namespace musical::core::guitar::tuning
{
enum class Standard : uint8_t 
{ 
    LOW_E  = 0, 
    A      = 1, 
    D      = 2, 
    G      = 3, 
    B      = 4, 
    HIGH_E = 5 
};
enum class DROP_D : uint8_t
{
    D_LOW  = 0,
    A      = 1,
    D      = 2,
    G      = 3,
    B      = 4,
    HIGH_E = 5
};
enum class DADGAD : uint8_t
{ 
    D_LOW  = 0,
    A      = 1,
    D      = 2,
    G      = 3,
    A_HIGH = 4,
    D_HIGH = 5
};
enum class OPEN_D : uint8_t
{
    D_LOW  = 0,
    A      = 1,
    D      = 2,
    F_SHARP= 3,
    A_HIGH = 4,
    D_HIGH = 5
};
enum class OPEN_E : uint8_t
{
    LOW_E   = 0,
    B       = 1,
    E       = 2,
    G_SHARP = 3,
    B_HIGH  = 4,
    HIGH_E  = 5
};
enum class OPEN_G : uint8_t
{ 
    D_LOW  = 0,
    G      = 1,
    D      = 2,
    G_HIGH = 3,
    B      = 4,
    D_HIGH = 5
};
} // namespace musical::core::guitar::tuning