#pragma once

#include <musical/core/chord/Chord.h>

namespace musical::audio::players
{

class ChordPlayer
{
public:
    // Joue un accord avec Karplus-Strong
    static void play(const core::chord::Chord& chord,
              double strum_delay_ms = 20.0,
              bool downstroke = true);
};

}