#pragma once

#include <cstdint>
#include <string>

namespace musical::core::guitar
{
// Représente un doigt de la main gauche (guitare)
enum class Finger : uint8_t
{
    NONE   = 0, 
    INDEX  = 1, 
    MIDDLE = 2, 
    RING   = 3, 
    PINKY  = 4, 
    THUMB  = 5  // pouce (rare mais utile pour certains grips)
};
} // namespace musical::core::guitar