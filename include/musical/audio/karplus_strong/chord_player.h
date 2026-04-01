#pragma once

#include <musical/core/chord/Chord.h>

namespace musical::audio::karplus_strong
{

class ChordPlayer
{
public:
    static void play(const core::chord::Chord& chord,
                     double strum_delay_ms,
                     bool downstroke);

};

}