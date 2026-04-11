#include <musical/audio/players/ChordPlayer.h>
#include <musical/audio/synthesis/KarplusStrong.h>
#include <musical/audio/engine/AlsaEngine.h>


namespace musical::audio::players
{

void ChordPlayer::play(
    const core::chord::Chord& chord,
    double strum_delay_ms,
    bool downstroke)
{
    using namespace synthesis;
    using namespace engine;

    // 1. génération
    auto float_samples = KarplusStrong::generate(
        chord,
        strum_delay_ms,
        downstroke
    );

    // 2. conversion
    std::vector<int16_t> samples(float_samples.size());

    for (size_t i = 0; i < float_samples.size(); ++i)
    {
        samples[i] = (int16_t)(float_samples[i] * 30000);
    }

    // 3. playback
    AlsaEngine engine;

    if (!engine.init())
        return;

    engine.play(samples);
}

}