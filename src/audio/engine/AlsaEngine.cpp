#include <musical/audio/engine/AlsaEngine.h>

#include <alsa/asoundlib.h>
#include <iostream>

namespace musical::audio::engine
{

constexpr int SAMPLE_RATE = 44100;

AlsaEngine::AlsaEngine()
    : _handle(nullptr)
{
}

AlsaEngine::~AlsaEngine()
{
    if (_handle)
    {
        snd_pcm_drain(_handle);
        snd_pcm_close(_handle);
        _handle = nullptr;
    }
}

// ------------------------------------------------------------
// INIT
// ------------------------------------------------------------
bool AlsaEngine::init()
{
    if(_handle)
        return true;

    if (snd_pcm_open(&_handle, "pulse",
                     SND_PCM_STREAM_PLAYBACK, 0) < 0)
    {
        std::cerr << "ALSA open error\n";
        return false;
    }

    if (snd_pcm_set_params(
            _handle,
            SND_PCM_FORMAT_S16_LE,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            1,
            SAMPLE_RATE,
            1,
            100000   // latence plus propre
        ) < 0)
    {
        std::cerr << "ALSA config error\n";
        snd_pcm_close(_handle);
        _handle = nullptr;        
        return false;
    }

    return true;
}

// ------------------------------------------------------------
// PLAY
// ------------------------------------------------------------
void AlsaEngine::play(const std::vector<int16_t>& samples)
{
    if (!_handle)
    {
        std::cerr << "ALSA not initialized\n";
        return;
    }

    const int16_t* data = samples.data();
    int frames = samples.size();

    while (frames > 0)
    {
        int written = snd_pcm_writei(_handle, data, frames);

        if (written < 0)
            written = snd_pcm_recover(_handle, written, 0);

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