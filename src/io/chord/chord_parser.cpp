
#include <musical/io/chord/chord_parser.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/note/Factory.h>
#include <musical/Core/MusicalCoreEnums.h>

#include <stdexcept>
#include <cctype>
#include <string>
#include <vector>

namespace musical::chord_parsing {

using IT = IntervalType;

// Conversion sécurisée
static IntervalType iv(int semitones)
{
    if (semitones < 0 ||
        semitones > static_cast<int>(IntervalType::DOUBLE_OCTAVE))
        throw std::invalid_argument("Invalid semitone value");

    return static_cast<IntervalType>(semitones);
}

musical::Chord from_saxon_name(const std::string& name)
{
    if (name.empty())
        throw std::invalid_argument("empty chord name");

    // ─────────────────────────────
    // 1) Parse de la fondamentale
    // ─────────────────────────────
    std::size_t pos = 0;

    char letter = std::toupper(static_cast<unsigned char>(name[pos]));
    if (letter < 'A' || letter > 'G')
        throw std::invalid_argument("invalid chord root");

    std::string root_name(1, letter);
    ++pos;

    if (pos < name.size() && (name[pos] == '#' || name[pos] == 'b')) {
        root_name += name[pos];
        ++pos;
    }

    Note tonic = NoteFactory::create(root_name);

    // ─────────────────────────────
    // 2) Triade majeure par défaut
    // ─────────────────────────────
    std::vector<IntervalType> intervals {
        IT::TIERCE_MAJEURE,
        IT::QUINTE_JUSTE
    };

    std::string suffix = name.substr(pos);

    // ─────────────────────────────
    // 3) Qualité de base
    // ─────────────────────────────
    if (!suffix.empty())
    {
        // Mineur (mais pas "maj")
        if (suffix[0] == 'm' && suffix.rfind("maj", 0) != 0)
        {
            intervals = {
                IT::TIERCE_MINEURE,
                IT::QUINTE_JUSTE
            };
            suffix.erase(0, 1);
        }

        if (suffix.rfind("dim", 0) == 0)
        {
            intervals = {
                IT::TIERCE_MINEURE,
                IT::TRITON
            };
            suffix.erase(0, 3);
        }
        else if (suffix.rfind("aug", 0) == 0)
        {
            intervals = {
                IT::TIERCE_MAJEURE,
                IT::SIXTE_MINEURE
            };
            suffix.erase(0, 3);
        }
    }

    // ─────────────────────────────
    // 4) Extensions
    // ─────────────────────────────
    if (suffix == "7")
    {
        intervals.push_back(IT::SEPTIEME_MINEURE);
    }
    else if (suffix == "7M" || suffix == "maj7")
    {
        intervals.push_back(IT::SEPTIEME_MAJEURE);
    }
    else if (suffix == "9")
    {
        intervals.push_back(IT::SEPTIEME_MINEURE);
        intervals.push_back(IT::NEUVIEME_MAJEURE);
    }
    else if (suffix == "11")
    {
        intervals.push_back(IT::SEPTIEME_MINEURE);
        intervals.push_back(IT::NEUVIEME_MAJEURE);
        intervals.push_back(IT::ONZIEME);
    }
    else if (suffix == "13")
    {
        intervals.push_back(IT::SEPTIEME_MINEURE);
        intervals.push_back(IT::NEUVIEME_MAJEURE);
        intervals.push_back(IT::ONZIEME);
        intervals.push_back(IT::TREIZIEME_MAJEURE);
    }

    return Chord(tonic, intervals);
}

} // namespace musical::chord_parsing
