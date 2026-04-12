#include <musical/audio/synthesis/basicsignalsgenerator.h>
#include <cmath>
#include <random>

namespace musical::audio::synthesis::basicsignalsgenerator
{

constexpr int SAMPLE_RATE = 44100;

// ------------------------------------------------------------
// SINE
// ------------------------------------------------------------
std::vector<int16_t> sine(float freq, float duration)
{
    int total = SAMPLE_RATE * duration;
    std::vector<int16_t> out(total);

    for (int i = 0; i < total; ++i)
    {
        float t = (float)i / SAMPLE_RATE;
        float s = sin(2.0f * M_PI * freq * t);
        out[i] = (int16_t)(s * 30000);
    }

    return out;
}

// ------------------------------------------------------------
// SQUARE (test clipping / harsh)
// ------------------------------------------------------------
std::vector<int16_t> square(float freq, float duration)
{
    int total = SAMPLE_RATE * duration;
    std::vector<int16_t> out(total);

    for (int i = 0; i < total; ++i)
    {
        float t = (float)i / SAMPLE_RATE;
        float s = sin(2.0f * M_PI * freq * t);
        out[i] = (s > 0 ? 30000 : -30000);
    }

    return out;
}

// ------------------------------------------------------------
// NOISE (super utile pour debug)
// ------------------------------------------------------------
std::vector<int16_t> noise(float duration)
{
    int total = SAMPLE_RATE * duration;
    std::vector<int16_t> out(total);

    std::mt19937 rng;
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int i = 0; i < total; ++i)
    {
        out[i] = (int16_t)(dist(rng) * 30000);
    }

    return out;
}

// ------------------------------------------------------------
// SWEEP (excellent test audio)
// ------------------------------------------------------------
std::vector<int16_t> sweep(float f0, float f1, float duration)
{
    int total = SAMPLE_RATE * duration;
    std::vector<int16_t> out(total);

    for (int i = 0; i < total; ++i)
    {
        float t = (float)i / total;
        float freq = f0 + (f1 - f0) * t;

        float phase = 2.0f * M_PI * freq * ((float)i / SAMPLE_RATE);
        float s = sin(phase);

        out[i] = (int16_t)(s * 30000);
    }

    return out;
}

// ------------------------------------------------------------
// CHORD TEST (La mineur simple)
// ------------------------------------------------------------
std::vector<int16_t> chord_test()
{
    int total = SAMPLE_RATE * 2.0;
    std::vector<int16_t> out(total, 0);

    float freqs[] = {220.0f, 261.63f, 329.63f}; // A C E

    for (float f : freqs)
    {
        for (int i = 0; i < total; ++i)
        {
            float t = (float)i / SAMPLE_RATE;
            float s = sin(2.0f * M_PI * f * t);
            out[i] += (int16_t)(s * 10000); // mix
        }
    }

    return out;
}

}