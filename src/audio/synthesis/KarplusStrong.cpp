#include <musical/audio/synthesis/KarplusStrong.h>
#include <musical/core/Pitch.h>

#include <iostream> // DEBUG
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

#define DEBUG

namespace musical::audio::synthesis
{

namespace
{
    constexpr int SAMPLE_RATE = 44100;
    constexpr double DURATION = 1;

    double frequency_from_pitch(const musical::core::Pitch& p)
    {
        int midi = static_cast<int>(p.value());

        // 🎯 HACK : remonter de 3 octaves 
        // TODO : revoir la création des notes dans core::Chord
        //        actuellement lse notes creées sont à l'octave 0 (C0 = 8.1758 Hz).
        midi += 48;

        return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
    }
    // double frequency_from_pitch(const musical::core::Pitch& p)
    // {
    //     int midi = p.value(); // ✔️ direct

    //     return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
    // }


    // 🎸 une corde
    std::vector<float> generate_string(double frequency, int total_samples)
    {
        int buffer_size = std::max(2, (int)(SAMPLE_RATE / frequency));
        std::vector<float> buffer(buffer_size);

        static std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        // excitation (bruit)
        for (auto& s : buffer)
            s = dist(gen); // plus d'énergie

        std::vector<float> output(total_samples);

        float decay = 0.996f - (frequency * 0.0000005f); // dépend de la note
        int idx = 0;

        for (int i = 0; i < total_samples; ++i)
        {
            float current = buffer[idx];
            float next = buffer[(idx + 1) % buffer_size];

            float new_sample = decay * 0.5f * (current + next);

            buffer[idx] = new_sample;
            idx = (idx + 1) % buffer_size;

            output[i] = new_sample;
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
// 🎸 TEST : une seule corde
// ------------------------------------------------------------
std::vector<float> KarplusStrong::generate_single(double frequency)
{
    int total_samples = static_cast<int>(SAMPLE_RATE * DURATION);
    return generate_string(frequency, total_samples);
}

// ------------------------------------------------------------
// 🎵 CHORD GENERATION (amélioré)
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
    {
#ifdef DEBUG
        std::cout << "Note: " << (int)pitch.value() << " Freq: " << frequency_from_pitch(pitch) << " Hz\n";
#endif  
        freqs.push_back(frequency_from_pitch(pitch));
    }

    if (!downstroke)
        std::reverse(freqs.begin(), freqs.end());

    int delay_samples =
        static_cast<int>((strum_delay_ms / 1000.0) * SAMPLE_RATE);

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> jitter(-50, 50);

    // mix des cordes
    for (size_t s = 0; s < freqs.size(); ++s)
    {
        auto string_sound = generate_string(freqs[s], total_samples);

        // strum réaliste
        int offset = delay_samples * (int)s + jitter(gen);

        // dynamique des cordes (grave > aigu)
        float string_gain = 0.8f - 0.1f * s;

        for (int i = 0; i < total_samples; ++i)
        {
            int target = i + offset;
            if (target >= 0 && target < total_samples)
            {
                float t = (float)i / SAMPLE_RATE;
                float env = std::exp(-2.0f * t); // decay global

                mix[target] += string_sound[i] * string_gain * env;
            }
        }
    }

    // soft clipping léger
    for (auto& v : mix)
        v = std::tanh(v * 0.8f);

    return mix;
}

}