#include <musical/audio/karplus_strong/chord_player.h>
#include <musical/core/Pitch.h>

#include <cmath>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>

namespace musical::audio::karplus_strong
{

namespace
{
    constexpr int SAMPLE_RATE = 44100;
    constexpr double DURATION = 3.0;

    // ------------------------------------------------------------
    // Pitch → fréquence
    // ------------------------------------------------------------
    double frequency_from_pitch(const musical::core::Pitch& p)
    {
        int midi = static_cast<int>(p.value());
        return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
    }

    // ------------------------------------------------------------
    // WAV writer
    // ------------------------------------------------------------
    void write_wav(const std::vector<int16_t>& samples)
    {
        std::ofstream file("chord.wav", std::ios::binary);

        int data_size = samples.size() * sizeof(int16_t);
        int file_size = 36 + data_size;

        file.write("RIFF", 4);
        file.write(reinterpret_cast<const char*>(&file_size), 4);
        file.write("WAVE", 4);

        file.write("fmt ", 4);
        int subchunk1_size = 16;
        short audio_format = 1;
        short num_channels = 1;
        int byte_rate = SAMPLE_RATE * num_channels * 2;
        short block_align = num_channels * 2;
        short bits_per_sample = 16;

        file.write(reinterpret_cast<const char*>(&subchunk1_size), 4);
        file.write(reinterpret_cast<const char*>(&audio_format), 2);
        file.write(reinterpret_cast<const char*>(&num_channels), 2);
        file.write(reinterpret_cast<const char*>(&SAMPLE_RATE), 4);
        file.write(reinterpret_cast<const char*>(&byte_rate), 4);
        file.write(reinterpret_cast<const char*>(&block_align), 2);
        file.write(reinterpret_cast<const char*>(&bits_per_sample), 2);

        file.write("data", 4);
        file.write(reinterpret_cast<const char*>(&data_size), 4);
        file.write(reinterpret_cast<const char*>(samples.data()), data_size);
    }

    // ------------------------------------------------------------
    // 🎸 Karplus-Strong (VERSION STABLE)
    // ------------------------------------------------------------
    std::vector<double> generate_string(double frequency, int total_samples)
    {
        int buffer_size = std::max(2, static_cast<int>(SAMPLE_RATE / frequency));
        std::vector<double> buffer(buffer_size);

        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<> dist(-0.5, 0.5); // bruit réduit

        for (auto& s : buffer)
            s = dist(gen);

        std::vector<double> output(total_samples);

        double decay = 0.996;
        int idx = 0;
        double last = 0.0;

        for (int i = 0; i < total_samples; ++i)
        {
            double current = buffer[idx];

            // filtre + damping
            double next = 0.5 * (buffer[idx] + buffer[(idx + 1) % buffer_size]);
            next = decay * next + (1.0 - decay) * last;

            last = next;

            output[i] = current;

            buffer[idx] = next;
            idx = (idx + 1) % buffer_size;
        }

        // attaque douce
        int attack = SAMPLE_RATE * 0.005;
        for (int i = 0; i < attack && i < total_samples; ++i)
        {
            output[i] *= (double)i / attack;
        }

        return output;
    }
}

// ------------------------------------------------------------
// 🎵 PLAY CHORD
// ------------------------------------------------------------
void ChordPlayer::play(const core::chord::Chord& chord,
                       double strum_delay_ms,
                       bool downstroke)
{
    std::cout << "[AUDIO] Karplus-Strong guitar";

    if (strum_delay_ms > 0.0)
        std::cout << " (strum " << strum_delay_ms << " ms)";

    std::cout << "...\n";

    int total_samples = static_cast<int>(SAMPLE_RATE * DURATION);
    std::vector<double> mix(total_samples, 0.0);

    // fréquences
    std::vector<double> freqs;
    for (const auto& pitch : chord.notes())
        freqs.push_back(frequency_from_pitch(pitch));

    if (!downstroke)
        std::reverse(freqs.begin(), freqs.end());

    int delay_samples =
        static_cast<int>((strum_delay_ms / 1000.0) * SAMPLE_RATE);

    // mix des cordes
    for (size_t s = 0; s < freqs.size(); ++s)
    {
        auto string_sound = generate_string(freqs[s], total_samples);

        int offset = delay_samples * static_cast<int>(s);

        for (int i = 0; i < total_samples; ++i)
        {
            int target = i + offset;
            if (target < total_samples)
                mix[target] += string_sound[i] * 0.2; // gain réduit
        }
    }

    // normalisation
    double max_val = 0.0;
    for (double v : mix)
        max_val = std::max(max_val, std::abs(v));

    if (max_val > 0.0)
    {
        for (auto& v : mix)
            v /= max_val;
    }

    // conversion + soft clip
    std::vector<int16_t> samples(total_samples);

    for (int i = 0; i < total_samples; ++i)
    {
        double v = std::tanh(mix[i]);
        samples[i] = static_cast<int16_t>(v * 30000);
    }

    write_wav(samples);

    std::cout << "[AUDIO] Playing...\n";
    std::system("aplay chord.wav > /dev/null 2>&1");
}

} // namespace musical::audio::karplus_strong