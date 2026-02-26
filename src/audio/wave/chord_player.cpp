#include <musical/audio/wave/chord_player.h>
#include <musical/Core/pitch_t.h>

#include <cmath>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <random>

namespace musical::audio::wave
{

namespace
{
    constexpr int SAMPLE_RATE = 44100;
    constexpr double DURATION = 3.0;
    constexpr double PI = 3.141592653589793;

    double frequency_from_pitch(const musical::core::pitch_t& p)
    {
        int midi = (p.octave() + 1) * 12 + musical::core::chromatic_index(p);
        return 440.0 * std::pow(2.0, (midi - 69) / 12.0);
    }

    // 🎸 Enveloppe type corde pincée (rapide attaque, decay exponentiel)
    double pluck_envelope(double t)
    {
        double attack = 0.005; // 5 ms

        if (t < attack)
            return t / attack;

        // décroissance exponentielle
        return std::exp(-3.5 * t);
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
}

void ChordPlayer::play(const core::chord::Chord& chord)
{
    std::cout << "[AUDIO] Generating realistic guitar WAV...\n";

    int total_samples = static_cast<int>(SAMPLE_RATE * DURATION);
    std::vector<int16_t> samples(total_samples, 0);

    std::vector<double> freqs;

    for (const auto& pitch : chord.notes())
        freqs.push_back(frequency_from_pitch(pitch));

    // léger random pour désaccord naturel
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> detune(-0.003, 0.003);

    for (int i = 0; i < total_samples; ++i)
    {
        double t = static_cast<double>(i) / SAMPLE_RATE;
        double value = 0.0;

        for (double f : freqs)
        {
            double f_detuned = f * (1.0 + detune(gen));

            // 🎸 Spectre guitare : fondamentale + harmoniques décroissantes
            value +=
                1.0  * std::sin(2.0 * PI * f_detuned * t) +
                0.6  * std::sin(2.0 * PI * f_detuned * 2 * t) +
                0.3  * std::sin(2.0 * PI * f_detuned * 3 * t) +
                0.15 * std::sin(2.0 * PI * f_detuned * 4 * t);
        }

        value /= freqs.size();

        // 🎸 enveloppe corde pincée
        value *= pluck_envelope(t);

        // saturation douce (évite clipping brutal)
        value = std::tanh(value);

        samples[i] = static_cast<int16_t>(value * 30000);
    }

    write_wav(samples);

    std::cout << "[AUDIO] Playing...\n";
    std::system("aplay chord.wav > /dev/null 2>&1");
}

} // namespace