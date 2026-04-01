#include <musical/core/scale/ScaleKeyedFactory.h>
#include <musical/core/Pitch.h>

#include <algorithm>
#include <stdexcept>

namespace musical::core::scale
{

// ------------------------------------------------------------
// Helper : normalize chromatic value
// ------------------------------------------------------------
static int normalize(int v)
{
    return ((v % 12) + 12) % 12;
}


// ------------------------------------------------------------
// Create from ScalePattern + Pitch
// ------------------------------------------------------------
ScaleKeyed ScaleKeyedFactory::create(
    const ScalePattern& scale,
    const Pitch& tonic,
    bool /*with_sharp*/)
{
    ScaleKeyed gamme;

    uint8_t current = tonic.value();

    for (int interval : scale.get_intervals())
    {
        gamme += Pitch(current);
        current = static_cast<uint8_t>(current + interval);
    }

    return gamme;
}


// ------------------------------------------------------------
// Create from repeated interval
// ------------------------------------------------------------
ScaleKeyed ScaleKeyedFactory::create(
    Interval interval,
    const Pitch& tonic,
    bool /*with_sharp*/)
{
    ScaleKeyed gamme;

    gamme += tonic;

    uint8_t start   = tonic.value();
    uint8_t current = start;

    for (;;)
    {
        current = static_cast<uint8_t>(current + static_cast<uint8_t>(interval));

        if ((current % 12) == (start % 12))
            break;

        gamme += Pitch(current);
    }

    return gamme;
}


// ------------------------------------------------------------
// Chromatic set generator
// ------------------------------------------------------------
std::array<std::string,12>
ScaleKeyedFactory::get_chromatique_set(
    bool with_sharp,
    const Pitch& note_begin)
{
    static std::array<std::string,12> sharp_set =
    { "c","c#","d","d#","e","f","f#","g","g#","a","a#","b" };

    static std::array<std::string,12> flat_set =
    { "c","db","d","eb","e","f","gb","g","ab","a","bb","b" };

    auto set = with_sharp ? sharp_set : flat_set;

    int pos = static_cast<int>(note_begin.tone());

    std::rotate(set.begin(), set.begin() + pos, set.end());

    return set;
}

} // namespace musical::core::scale