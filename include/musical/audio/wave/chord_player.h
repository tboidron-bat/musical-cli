#pragma once

#include <musical/core/chord/Chord.h>

namespace musical::audio::wave
{

class ChordPlayer
{
public:
    static void play(const core::chord::Chord& chord);
};

}