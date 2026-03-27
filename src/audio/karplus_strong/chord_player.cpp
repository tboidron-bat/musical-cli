#include <musical/audio/karplus_strong/chord_player.h>
#include <musical/Core/Pitch.h>

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

    double frequency_from_pitch(const musical::core::Pitch& p)
    {
        int midi = static_cast<int>(p.value());
        return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
    }
    
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

    // 🎸 Générateur Karplus-Strong pour une fréquence
    std::vector<double> generate_string(double frequency, int total_samples)
    {
        int buffer_size = static_cast<int>(SAMPLE_RATE / frequency);
        std::vector<double> buffer(buffer_size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-1.0, 1.0);

        // Initialisation bruit blanc
        for (auto& s : buffer)
            s = dist(gen);

        std::vector<double> output(total_samples);

        double decay = 0.996; // contrôle sustain

        for (int i = 0; i < total_samples; ++i)
        {
            double current = buffer[0];
            double next = decay * 0.5 * (buffer[0] + buffer[1]);

            output[i] = current;

            buffer.erase(buffer.begin());
            buffer.push_back(next);
        }

        return output;
    }
}

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

    // Récupération des fréquences
    std::vector<double> freqs;
    for (const auto& pitch : chord.notes())
        freqs.push_back(frequency_from_pitch(pitch));

    if (!downstroke)
        std::reverse(freqs.begin(), freqs.end());

    // Conversion ms -> samples
    int delay_samples =
        static_cast<int>((strum_delay_ms / 1000.0) * SAMPLE_RATE);

    for (size_t s = 0; s < freqs.size(); ++s)
    {
        double freq = freqs[s];
        auto string_sound = generate_string(freq, total_samples);

        int offset = delay_samples * static_cast<int>(s);

        for (int i = 0; i < total_samples; ++i)
        {
            int target = i + offset;
            if (target < total_samples)
                mix[target] += string_sound[i];
        }
    }

    // Normalisation + saturation douce
    std::vector<int16_t> samples(total_samples);

    for (int i = 0; i < total_samples; ++i)
    {
        double v = mix[i] / freqs.size();
        v = std::tanh(v);
        samples[i] = static_cast<int16_t>(v * 30000);
    }

    write_wav(samples);

    std::cout << "[AUDIO] Playing...\n";
    std::system("aplay chord.wav > /dev/null 2>&1");
}
} // namespace