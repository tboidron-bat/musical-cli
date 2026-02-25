#include <musical/Core/scale/ScaleKeyedFactory.h>
#include <musical/Core/pitch_t.h>

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
// Create from ScalePattern + pitch_t
// ------------------------------------------------------------
ScaleKeyed ScaleKeyedFactory::create(
    const ScalePattern& scale,
    const pitch_t& tonic,
    bool with_sharp)
{
    ScaleKeyed gamme;

    int current = static_cast<int>(chromatic_index(tonic));
    int octave  = tonic._octave;

    for (int interval : scale.get_intervals())
    {
        pitch_t p = pitch_from_chromatic(current, with_sharp);
        p._octave = octave;

        gamme += p;

        current = normalize(current + interval);
    }

    return gamme;
}


// ------------------------------------------------------------
// Create from repeated interval
// ------------------------------------------------------------
ScaleKeyed ScaleKeyedFactory::create(
    IntervalType interval,
    const pitch_t& tonic,
    bool with_sharp)
{
    ScaleKeyed gamme;

    gamme += tonic;

    int start   = static_cast<int>(chromatic_index(tonic));
    int current = start;
    int octave  = tonic._octave;

    for (;;)
    {
        current = normalize(current + static_cast<int>(interval));

        if (current == start)
            break;

        pitch_t p = pitch_from_chromatic(current, with_sharp);
        p._octave = octave;

        gamme += p;
    }

    return gamme;
}


// ------------------------------------------------------------
// Chromatic set generator
// ------------------------------------------------------------
std::array<std::string,12>
ScaleKeyedFactory::get_chromatique_set(
    bool with_sharp,
    const pitch_t& note_begin)
{
    static std::array<std::string,12> sharp_set =
    { "c","c#","d","d#","e","f","f#","g","g#","a","a#","b" };

    static std::array<std::string,12> flat_set =
    { "c","db","d","eb","e","f","gb","g","ab","a","bb","b" };

    auto set = with_sharp ? sharp_set : flat_set;

    int pos = static_cast<int>(chromatic_index(note_begin));

    std::rotate(set.begin(), set.begin() + pos, set.end());

    return set;
}

} // namespace musical::core::scale