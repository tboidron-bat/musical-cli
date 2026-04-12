#pragma once

#include <vector>
#include <cstdint>


#include <alsa/asoundlib.h>

namespace musical::audio::engine
{
class AlsaEngine
{
public:
    AlsaEngine();
    ~AlsaEngine();

    bool init();
    void play(const std::vector<int16_t>& samples);

private:
    snd_pcm_t* _handle = nullptr;

};
}