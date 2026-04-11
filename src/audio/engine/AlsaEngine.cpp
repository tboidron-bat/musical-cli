#include <musical/audio/engine/AlsaEngine.h>

#include <alsa/asoundlib.h>
#include <iostream>

namespace musical::audio::engine
{

constexpr int SAMPLE_RATE = 44100;

// ------------------------------------------------------------
// Impl interne (ALSA caché)
// ------------------------------------------------------------
struct AlsaEngine::Impl
{
    snd_pcm_t* handle = nullptr;
};

// ------------------------------------------------------------
// CTOR / DTOR
// ------------------------------------------------------------
AlsaEngine::AlsaEngine()
{
    impl = new Impl();
}

AlsaEngine::~AlsaEngine()
{
    if (impl->handle)
    {
        snd_pcm_drain(impl->handle);
        snd_pcm_close(impl->handle);
    }

    delete impl;
}

// ------------------------------------------------------------
// INIT
// ------------------------------------------------------------
bool AlsaEngine::init()
{
    if (snd_pcm_open(&impl->handle, "pulse",
                     SND_PCM_STREAM_PLAYBACK, 0) < 0)
    {
        std::cerr << "ALSA open error\n";
        return false;
    }

    if (snd_pcm_set_params(
            impl->handle,
            SND_PCM_FORMAT_S16_LE,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            1,
            SAMPLE_RATE,
            1,
            100000   // latence plus propre
        ) < 0)
    {
        std::cerr << "ALSA config error\n";
        return false;
    }

    return true;
}

// ------------------------------------------------------------
// PLAY
// ------------------------------------------------------------
void AlsaEngine::play(const std::vector<int16_t>& samples)
{
    if (!impl->handle)
    {
        std::cerr << "ALSA not initialized\n";
        return;
    }

    const int16_t* data = samples.data();
    int frames = samples.size();

    while (frames > 0)
    {
        int written = snd_pcm_writei(impl->handle, data, frames);

        if (written < 0)
            written = snd_pcm_recover(impl->handle, written, 0);

        if (written < 0)
        {
            std::cerr << "ALSA write error\n";
            break;
        }

        frames -= written;
        data += written;
    }
}
}
// #include <alsa/asoundlib.h>
// #include <cmath>
// #include <vector>
// #include <iostream>

// namespace musical::audio
// {
//     const int sampleRate = 44100;
//     const float frequency = 440.0f; // La
//     const int duration = 2; // secondes

// std::vector<int16_t> generate_sine_wave(float freq, int sampleRate, int duration)
// {
//     int totalSamples = sampleRate * duration;
//     std::vector<int16_t> samples(totalSamples);

//     for (int i = 0; i < totalSamples; ++i)
//     {
//         float t = (float)i / sampleRate;
//         float s = sin(2.0f * M_PI * freq * t);
//         samples[i] = (int16_t)(s * 30000); // conversion 16 bits
//     }

//     return samples;
// }    
// snd_pcm_t* alsa_init()
// {
//     snd_pcm_t* handle;

//     snd_pcm_open(&handle, "pulse", SND_PCM_STREAM_PLAYBACK, 0);

//     // if (snd_pcm_open(&handle, "plughw:CARD=PCH,DEV=0",
//     //                  SND_PCM_STREAM_PLAYBACK, 0) < 0)
//     // {
//     //     std::cerr << "Erreur ouverture ALSA\n";
//     //     return nullptr;
//     // }

//     if (snd_pcm_set_params(
//             handle,
//             SND_PCM_FORMAT_S16_LE,        // format standard
//             SND_PCM_ACCESS_RW_INTERLEAVED,
//             1,                           // mono
//             sampleRate,
//             1,
//             500000                       // latency (µs)
//         ) < 0)
//     {
//         std::cerr << "Erreur config ALSA\n";
//         return nullptr;
//     }
//     return handle;
// }
// int alsa_test()
// {
//     std::cout << "Testing ALSA audio output...\n";

//     int totalSamples = sampleRate * duration;

//     // ------------------------------------------------------------
//     // Générer un sinus
//     // ------------------------------------------------------------
//     std::vector<int16_t> samples = generate_sine_wave(frequency, sampleRate, duration);


//     snd_pcm_t* handle = alsa_init();

//     if (!handle)
//     {
//         std::cerr << "ALSA init failed\n";
//         return 1;
//     }    
//     // ------------------------------------------------------------
//     // Playback
//     // ------------------------------------------------------------
//     const int16_t* data = samples.data();
//     int frames = totalSamples;

//     while (frames > 0)
//     {
//         int written = snd_pcm_writei(handle, data, frames);

//         if (written < 0)
//             written = snd_pcm_recover(handle, written, 0);

//         if (written < 0)
//         {
//             std::cerr << "Erreur écriture\n";
//             break;
//         }

//         frames -= written;
//         data += written;
//     }

//     snd_pcm_drain(handle);
//     snd_pcm_close(handle);

//     return 0;
// }