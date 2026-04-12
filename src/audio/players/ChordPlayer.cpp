#include <musical/audio/players/ChordPlayer.h>
#include <musical/audio/synthesis/KarplusStrong.h>
#include <musical/audio/engine/AlsaEngine.h>

#include <musical/audio/synthesis/basicsignalsgenerator.h> // pour les tests


namespace musical::audio::players
{

void ChordPlayer::play(
    const core::chord::Chord& chord,
    double strum_delay_ms,
    bool downstroke)
{
    using namespace musical::audio::synthesis;
    using namespace musical::audio::engine;

    // // 1. génération
    auto float_samples = musical::audio::synthesis::KarplusStrong::generate(
        chord,
        strum_delay_ms,
        downstroke
    );

    // // 2. conversion
    std::vector<int16_t> samples(float_samples.size());

    for (size_t i = 0; i < float_samples.size(); ++i)
    {
        samples[i] = (int16_t)(float_samples[i] * 30000);
    }

    // 3. playback
    AlsaEngine engine;

    if (!engine.init())
        return;

    // test sine
    //auto samples_sine = basicsignalsgenerator::sine(220.0f, 2.0f); test ok

     // test square    
    //auto samples_square = basicsignalsgenerator::square(440.0f, 2.0f); // test ok. son d'alarme

    // test noise
    //auto samples_noise = basicsignalsgenerator::noise(2.0f); // test ok. bruit genre explosion

    // test sweep. 
     //auto samples_sweep = basicsignalsgenerator::sweep(100.0f, 2000.0f, 3.0f); // test ok. on entend bien la montée en fréquence
    
    // test accord
    //auto samples_chord = basicsignalsgenerator::chord_test(); // test ok. on entend un bruit bizarre.


    // TEST Karplus one string ok
    // auto float_samples_test = KarplusStrong::generate_single(110.0);

    // std::vector<int16_t> samples(float_samples_test.size());

    // constexpr float GAIN = 0.9f;

    // for (size_t i = 0; i < float_samples_test.size(); ++i)
    // {
    //     samples[i] = (int16_t)(float_samples_test[i] * GAIN * 32767);
    // }

    engine.play(samples);}

}