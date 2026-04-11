#pragma once

#include <vector>
#include <cstdint>

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
    struct Impl;
    Impl* impl; // pour cacher ALSA (pas dans le header)
};
}