#pragma once

#include <vector>
#include <cstdint>

namespace musical::audio::synthesis::basicsignalsgenerator
{

std::vector<int16_t> sine(float freq, float duration);
std::vector<int16_t> square(float freq, float duration);
std::vector<int16_t> noise(float duration);
std::vector<int16_t> sweep(float f0, float f1, float duration);

// bonus
std::vector<int16_t> chord_test();

}