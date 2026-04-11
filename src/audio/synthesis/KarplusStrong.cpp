#include <musical/audio/synthesis/KarplusStrong.h>
#include <musical/core/Pitch.h>

#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace musical::audio::synthesis
{

namespace
{
    constexpr int SAMPLE_RATE = 44100;
    constexpr double DURATION = 3.0;

    double frequency_from_pitch(const musical::core::Pitch& p)
    {
        int midi = static_cast<int>(p.value());
        return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
    }

    // 🎸 une corde
    std::vector<float> generate_string(double frequency, int total_samples)
    {
        int buffer_size = std::max(2, (int)(SAMPLE_RATE / frequency));
        std::vector<float> buffer(buffer_size);

        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        for (auto& s : buffer)
            s = dist(gen) * 0.3f; // bruit contrôlé

        std::vector<float> output(total_samples);

        float decay = 0.996f;
        int idx = 0;

        for (int i = 0; i < total_samples; ++i)
        {
            float current = buffer[idx];
            float next = buffer[(idx + 1) % buffer_size];

            float new_sample = decay * 0.5f * (current + next);

            buffer[idx] = new_sample;
            idx = (idx + 1) % buffer_size;

            output[i] = new_sample; // ✅ important
        }

        // attaque douce
        int attack = SAMPLE_RATE * 0.005;
        for (int i = 0; i < attack && i < total_samples; ++i)
        {
            output[i] *= (float)i / attack;
        }

        return output;
    }
}

// ------------------------------------------------------------
// 🎵 CHORD GENERATION
// ------------------------------------------------------------
std::vector<float> KarplusStrong::generate(const core::chord::Chord& chord,
                                           double strum_delay_ms,
                                           bool downstroke)
{
    int total_samples = static_cast<int>(SAMPLE_RATE * DURATION);
    std::vector<float> mix(total_samples, 0.0f);

    // fréquences
    std::vector<double> freqs;
    for (const auto& pitch : chord.notes())
        freqs.push_back(frequency_from_pitch(pitch));

    if (!downstroke)
        std::reverse(freqs.begin(), freqs.end());

    int delay_samples =
        static_cast<int>((strum_delay_ms / 1000.0) * SAMPLE_RATE);

    float gain = 1.0f / std::max(1, (int)freqs.size());

    // mix des cordes
    for (size_t s = 0; s < freqs.size(); ++s)
    {
        auto string_sound = generate_string(freqs[s], total_samples);

        int offset = delay_samples * (int)s;

        for (int i = 0; i < total_samples; ++i)
        {
            int target = i + offset;
            if (target < total_samples)
                mix[target] += string_sound[i] * gain;
        }
    }

    // normalisation + soft clip
    for (auto& v : mix)
        v = std::tanh(v);

    return mix;
}

}