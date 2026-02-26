#include <musical/ScoreElements/KeySignature.h>
#include <musical/Core/pitch_t.h>
#include <musical/Core/scale/ScaleKeyedFactory.h>
#include <musical/io/note/output/note_formatter.h>

#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <map>
#include <stdexcept>

namespace musical::score {

// ============================================================
// Mode parsing
// ============================================================

KeyModeType KeySignature::mode_from_string(const std::string& name_input)
{
    static const std::unordered_map<std::string, KeyModeType> mode_map = {
        {"ionian", KeyModeType::IONIAN},
        {"dorian", KeyModeType::DORIAN},
        {"phrygian", KeyModeType::PHRYGIAN},
        {"lydian", KeyModeType::LYDIAN},
        {"mixolydian", KeyModeType::MIXOLYDIAN},
        {"aeolian", KeyModeType::AEOLIAN},
        {"locrian", KeyModeType::LOCRIAN}
    };

    std::string name = name_input;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = mode_map.find(name);
    if (it != mode_map.end())
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
        case KeyModeType::AEOLIAN:    return "aeolian";
        case KeyModeType::DORIAN:     return "dorian";
        case KeyModeType::PHRYGIAN:   return "phrygian";
        case KeyModeType::LYDIAN:     return "lydian";
        case KeyModeType::MIXOLYDIAN: return "mixolydian";
        case KeyModeType::LOCRIAN:    return "locrian";
    }

    throw std::invalid_argument("[KeySignature::to_string] unknown mode");
}

std::string KeySignature::to_french(KeyModeType m)
{
    switch (m)
    {
        case KeyModeType::IONIAN:     return "ionien";
        case KeyModeType::AEOLIAN:    return "éolien";
        case KeyModeType::DORIAN:     return "dorien";
        case KeyModeType::PHRYGIAN:   return "phrygien";
        case KeyModeType::LYDIAN:     return "lydien";
        case KeyModeType::MIXOLYDIAN: return "mixolydien";
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

    auto gamme = core::scale::ScaleKeyedFactory::create(
        core::IntervalType::QUINTE_JUSTE,
        pitch
    );

    gamme.truncate(SHARP_KEY_COUNT);

    for (std::size_t i = 0; i < SHARP_KEY_COUNT; ++i)
    {
        result[i] =
            musical::io::note::formatter::to_string(gamme[i+1]);
    }

    return result;
}

std::array<std::string, FLAT_KEY_COUNT>
KeySignature::circle_fourths(const core::pitch_t& pitch)
{
    std::array<std::string, FLAT_KEY_COUNT> result{};

    auto gamme = core::scale::ScaleKeyedFactory::create(
        core::IntervalType::QUARTE_JUSTE,
        pitch,
        false
    );

    gamme.truncate(FLAT_KEY_COUNT);

    for (std::size_t i = 0; i < FLAT_KEY_COUNT; ++i)
    {
        result[i] =
            musical::io::note::formatter::to_string(gamme[i]);
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
    KeyModeType mode = mode_from_string(mei_mode);

    // Pour simplifier et éviter la duplication monstrueuse :
    // on utilise le cercle approprié

    core::pitch_t base{ core::NoteName::C, core::Accidental::NONE, 4 };

    if (mode == KeyModeType::AEOLIAN)
        base = { core::NoteName::A, core::Accidental::NONE, 4 };

    auto sharps = circle_fifths(base);
    auto flats  = circle_fourths(base);

    if (mei_keysig == "0")
        return musical::io::note::formatter::to_string(base);

    if (mei_keysig.back() == 's')
    {
        int n = mei_keysig[0] - '0';
        return sharps[n-1];
    }

    if (mei_keysig.back() == 'f')
    {
        int n = mei_keysig[0] - '0';
        return flats[n-1];
    }

    throw std::runtime_error("[KeySignature::from_mei] invalid mei_keysig");
}

// ============================================================
// Key → MEI
// ============================================================

std::string KeySignature::to_mei_string(
    KeyModeType mode,
    const core::pitch_t& tonality)
{
    core::pitch_t base{ core::NoteName::C, core::Accidental::NONE, 4 };

    if (mode == KeyModeType::AEOLIAN)
        base = { core::NoteName::A, core::Accidental::NONE, 4 };

    auto sharps = circle_fifths(base);
    auto flats  = circle_fourths(base);

    std::string n =
        musical::io::note::formatter::to_string(tonality);

    if (n == musical::io::note::formatter::to_string(base))
        return "0";

    for (std::size_t i = 0; i < sharps.size(); ++i)
        if (sharps[i] == n)
            return std::to_string(i+1) + "s";

    for (std::size_t i = 0; i < flats.size(); ++i)
        if (flats[i] == n)
            return std::to_string(i+1) + "f";

    throw std::runtime_error("[KeySignature::to_mei_string] failure");
}

} // namespace musical::score