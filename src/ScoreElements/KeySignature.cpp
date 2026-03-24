#include <musical/ScoreElements/KeySignature.h>
#include <musical/Core/pitch_t.h>
#include <musical/Core/scale/ScaleKeyedFactory.h>

#include <algorithm>
#include <unordered_map>
#include <stdexcept>
#include <sstream>

namespace musical::score {

// ============================================================
// Helpers
// ============================================================

static std::string to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return s;
}

// 🔥 nouveau helper (remplace note_formatter)
static std::string pitch_to_string(const core::pitch_t& p)
{
    std::ostringstream oss;
    oss << p;
    return oss.str();
}

static core::pitch_t base_pitch(KeyModeType mode)
{
    using core::NoteName;
    using core::Accidental;

    if (mode == KeyModeType::AEOLIAN)
        return { NoteName::A, Accidental::NONE, 4 };

    return { NoteName::C, Accidental::NONE, 4 };
}

// ============================================================
// Mode parsing
// ============================================================

KeyModeType KeySignature::mode_from_string(const std::string& input)
{
    static const std::unordered_map<std::string, KeyModeType> map = {
        {"ionian", KeyModeType::IONIAN},
        {"dorian", KeyModeType::DORIAN},
        {"phrygian", KeyModeType::PHRYGIAN},
        {"lydian", KeyModeType::LYDIAN},
        {"mixolydian", KeyModeType::MIXOLYDIAN},
        {"aeolian", KeyModeType::AEOLIAN},
        {"locrian", KeyModeType::LOCRIAN}
    };

    auto name = to_lower(input);

    if (auto it = map.find(name); it != map.end())
        return it->second;

    throw std::invalid_argument(
        "[KeySignature::mode_from_string] invalid mode '" + name + "'"
    );
}

// ============================================================
// Mode stringification
// ============================================================

std::string KeySignature::to_string(KeyModeType m)
{
    switch (m)
    {
        case KeyModeType::IONIAN:     return "ionian";
        case KeyModeType::DORIAN:     return "dorian";
        case KeyModeType::PHRYGIAN:   return "phrygian";
        case KeyModeType::LYDIAN:     return "lydian";
        case KeyModeType::MIXOLYDIAN: return "mixolydian";
        case KeyModeType::AEOLIAN:    return "aeolian";
        case KeyModeType::LOCRIAN:    return "locrian";
    }

    throw std::invalid_argument("[KeySignature::to_string] unknown mode");
}

std::string KeySignature::to_french(KeyModeType m)
{
    switch (m)
    {
        case KeyModeType::IONIAN:     return "ionien";
        case KeyModeType::DORIAN:     return "dorien";
        case KeyModeType::PHRYGIAN:   return "phrygien";
        case KeyModeType::LYDIAN:     return "lydien";
        case KeyModeType::MIXOLYDIAN: return "mixolydien";
        case KeyModeType::AEOLIAN:    return "éolien";
        case KeyModeType::LOCRIAN:    return "locrien";
    }

    throw std::invalid_argument("[KeySignature::to_french] unknown mode");
}

// ============================================================
// Circle of fifths / fourths
// ============================================================

std::array<std::string, SHARP_KEY_COUNT>
KeySignature::circle_fifths(const core::pitch_t& pitch)
{
    std::array<std::string, SHARP_KEY_COUNT> result{};

    auto scale = core::scale::ScaleKeyedFactory::create(
        core::Interval::PERFECT_FIFTH,
        pitch
    );

    scale.truncate(SHARP_KEY_COUNT);

    for (std::size_t i = 0; i < SHARP_KEY_COUNT; ++i)
    {
        result[i] = pitch_to_string(scale[i + 1]);
    }

    return result;
}

std::array<std::string, FLAT_KEY_COUNT>
KeySignature::circle_fourths(const core::pitch_t& pitch)
{
    std::array<std::string, FLAT_KEY_COUNT> result{};

    auto scale = core::scale::ScaleKeyedFactory::create(
        core::Interval::PERFECT_FOURTH,
        pitch,
        false
    );

    scale.truncate(FLAT_KEY_COUNT);

    for (std::size_t i = 0; i < FLAT_KEY_COUNT; ++i)
    {
        result[i] = pitch_to_string(scale[i]);
    }

    return result;
}

// ============================================================
// MEI → Key
// ============================================================

std::string KeySignature::from_mei(
    const std::string& mei_mode,
    const std::string& mei_keysig)
{
    auto mode = mode_from_string(mei_mode);
    auto base = base_pitch(mode);

    auto sharps = circle_fifths(base);
    auto flats  = circle_fourths(base);

    if (mei_keysig == "0")
        return pitch_to_string(base);

    if (mei_keysig.size() < 2)
        throw std::runtime_error("[KeySignature::from_mei] invalid format");

    int n = mei_keysig[0] - '0';

    if (mei_keysig.back() == 's')
        return sharps[n - 1];

    if (mei_keysig.back() == 'f')
        return flats[n - 1];

    throw std::runtime_error("[KeySignature::from_mei] invalid mei_keysig");
}

// ============================================================
// Key → MEI
// ============================================================

std::string KeySignature::to_mei_string(
    KeyModeType mode,
    const core::pitch_t& tonality)
{
    auto base = base_pitch(mode);

    auto sharps = circle_fifths(base);
    auto flats  = circle_fourths(base);

    auto n = pitch_to_string(tonality);
    auto base_str = pitch_to_string(base);

    if (n == base_str)
        return "0";

    for (std::size_t i = 0; i < sharps.size(); ++i)
        if (sharps[i] == n)
            return std::to_string(i + 1) + "s";

    for (std::size_t i = 0; i < flats.size(); ++i)
        if (flats[i] == n)
            return std::to_string(i + 1) + "f";

    throw std::runtime_error("[KeySignature::to_mei_string] failure");
}

} // namespace musical::score