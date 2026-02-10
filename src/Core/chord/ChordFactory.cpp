#include <musical/Core/chord/ChordFactory.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/note/Note.h>
#include <musical/Core/ScaleKeyed.h>
#include <musical/Core/note/NoteService.h>
#include <musical/IO/chord/chord_parser.h>

#include <stdexcept>
#include <map>

namespace musical {

namespace {

using IT = IntervalType;

// -----------------------------------------------------------------------------
// Conversion sécurisée demi-tons -> IntervalType
// -----------------------------------------------------------------------------
IntervalType interval_from_semitones(int semitones)
{
    if (semitones < 0 ||
        semitones > static_cast<int>(IntervalType::DOUBLE_OCTAVE))
    {
        throw std::invalid_argument("Invalid semitone value for IntervalType");
    }

    return static_cast<IntervalType>(semitones);
}

// -----------------------------------------------------------------------------
// Table des accords communs
// -----------------------------------------------------------------------------
static const std::map<CommonChordType, std::vector<IT>> COMMON_CHORD_INTERVALS = {

    // --- Triades ---
    { CommonChordType::MAJOR,            { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE } },
    { CommonChordType::MINOR,            { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE } },
    { CommonChordType::DIMINISHED,       { IT::TIERCE_MINEURE, IT::TRITON } },
    { CommonChordType::AUGMENTED,        { IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE } },

    // --- 7e ---
    { CommonChordType::DOMINANT7,        { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE } },
    { CommonChordType::MAJOR7,           { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE } },
    { CommonChordType::MINOR7,           { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE } },
    { CommonChordType::HALF_DIMINISHED7, { IT::TIERCE_MINEURE, IT::TRITON, IT::SEPTIEME_MINEURE } },
    { CommonChordType::DIMINISHED7,      { IT::TIERCE_MINEURE, IT::TRITON, IT::SIXTE_MAJEURE } },

    // --- 9 ---
    { CommonChordType::MAJOR9,           { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE } },
    { CommonChordType::DOMINANT9,        { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE } },
    { CommonChordType::MINOR9,           { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE } },

    // --- 11 ---
    { CommonChordType::MAJOR11,          { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME } },
    { CommonChordType::DOMINANT11,       { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME } },
    { CommonChordType::MINOR11,          { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME } },

    // --- 13 ---
    { CommonChordType::MAJOR13,          { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME, IT::TREIZIEME_MAJEURE } },
    { CommonChordType::DOMINANT13,       { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME, IT::TREIZIEME_MAJEURE } },
    { CommonChordType::MINOR13,          { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE, IT::NEUVIEME_MAJEURE, IT::ONZIEME, IT::TREIZIEME_MAJEURE } },

    // --- Suspensions / Add ---
    { CommonChordType::SUSPENDED2,       { IT::SECONDE_MAJEURE, IT::QUINTE_JUSTE } },
    { CommonChordType::SUSPENDED4,       { IT::QUARTE_JUSTE, IT::QUINTE_JUSTE } },
    { CommonChordType::ADD9,             { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::NEUVIEME_MAJEURE } },

    // --- Sixte ---
    { CommonChordType::MAJOR6,           { IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SIXTE_MAJEURE } },
    { CommonChordType::MINOR6,           { IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SIXTE_MAJEURE } },

    { CommonChordType::NOCHORD,          {} },
    { CommonChordType::UNKNOWN,          {} }
};

} // anonymous namespace


// -----------------------------------------------------------------------------
// Création depuis un type d'accord standard
// -----------------------------------------------------------------------------
Chord ChordFactory::create(const Note& root, CommonChordType type)
{
    auto it = COMMON_CHORD_INTERVALS.find(type);

    if (it == COMMON_CHORD_INTERVALS.end())
        throw std::invalid_argument("Unknown CommonChordType");

    return Chord(root, it->second);
}


// -----------------------------------------------------------------------------
// Création depuis une gamme (empilement de tierces)
// -----------------------------------------------------------------------------
Chord ChordFactory::create(const Note& root,
                           const ScaleKeyed& scale,
                           ChordClassType nb_notes)
{
    std::vector<IntervalType> intervals;

    int root_pc = NoteService::chromatic_index(root);

    for (int i = 1; i < static_cast<int>(nb_notes); ++i)
    {
        int degree = i * 2;
        const Note& n = scale[degree % scale.size()];

        int pc = NoteService::chromatic_index(n);
        int semitones = pc - root_pc;

        if (semitones < 0)
            semitones += 12;

        intervals.push_back(interval_from_semitones(semitones));
    }

    return Chord(root, intervals);
}


// -----------------------------------------------------------------------------
// Création depuis un nom anglo-saxon (parser)
// -----------------------------------------------------------------------------
Chord ChordFactory::create(const std::string& name_en)
{
    return musical::chord_parsing::from_saxon_name(name_en);
}

} // namespace musical
