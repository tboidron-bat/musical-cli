#pragma once

#include <musical/core/chord/Chord.h>

namespace musical::audio::synthesis
{

class KarplusStrong
{
public:
    static std::vector<float> 
        generate(const core::chord::Chord& chord,
            double strum_delay_ms,
            bool downstroke);

    static std::vector<float> generate_single(double frequency);

};

}