#include <musical/analysis/chord_name.h>
#include <musical/Core/chord/Chord.h>
#include <musical/io/note/note_formatter.h>
#include <musical/Core/intervals_defs.h>

#include <algorithm>
#include <stdexcept>

namespace musical::analysis::chord_name {

using IT = musical::core::IntervalType;

// ============================================================
// Dispatcher
// ============================================================
std::vector<candidate>
find(const core::Chord& chord)
{
    if (chord.size() < 2)
        return {};

    std::vector<candidate> results;

    switch (chord.size())
    {
        case 2: results = analyse_dyad(chord);   break;
        case 3: results = analyse_triad(chord);  break;
        case 4: results = analyse_tetrade(chord); break;
        default: break;
    }

    // filtrer le bruit
    results.erase(
        std::remove_if(results.begin(), results.end(),
            [](const candidate& c) { return c.score <= 0; }),
        results.end()
    );

    std::sort(results.begin(), results.end(),
        [](const candidate& a, const candidate& b)
        {
            return a.score > b.score;
        });

    return results;
}

// ============================================================
// DYAD
// ============================================================
std::vector<candidate>
analyse_dyad(const core::Chord& chord)
{
    if (chord.size() != 2)
        throw std::logic_error("analyse_dyad: chord.size() != 2");

    std::vector<candidate> results;

    const auto& ivs = chord.intervals();
    IT iv = ivs.front();

    std::string root = 
        musical::io::note::formatter::to_string(chord.tonic());

    switch (iv)
    {
        case IT::SECONDE_MINEURE: results.push_back({ root + "b2", 6 }); break;
        case IT::SECONDE_MAJEURE: results.push_back({ root + "2", 6 }); break;
        case IT::TIERCE_MINEURE:  results.push_back({ root + "b3", 7 }); break;
        case IT::TIERCE_MAJEURE:  results.push_back({ root + "3", 7 }); break;
        case IT::QUARTE_JUSTE:    results.push_back({ root + "4", 6 }); break;
        case IT::TRITON:          results.push_back({ root + "b5", 6 }); break;
        case IT::QUINTE_JUSTE:    results.push_back({ root + "5", 8 }); break;
        case IT::SIXTE_MINEURE:   results.push_back({ root + "b6", 5 }); break;
        case IT::SIXTE_MAJEURE:   results.push_back({ root + "6", 5 }); break;
        case IT::SEPTIEME_MINEURE: results.push_back({ root + "7", 6 }); break;
        case IT::SEPTIEME_MAJEURE: results.push_back({ root + "7M", 6 }); break;
        default: break;
    }

    return results;
}

// ============================================================
// TRIAD
// ============================================================
std::vector<candidate>
analyse_triad(const core::Chord& chord)
{
    if (chord.size() != 3)
        throw std::logic_error("analyse_triad: chord.size() != 3");

    std::vector<candidate> results;
    const auto& iv = chord.intervals();

    std::string root =
        musical::io::note::formatter::to_string(chord.tonic());

    if (iv == std::vector<IT>{ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE })
        results.push_back({ root, 10 });

    else if (iv == std::vector<IT>{ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE })
        results.push_back({ root + "m", 10 });

    else if (iv == std::vector<IT>{ IT::TIERCE_MINEURE, IT::TRITON })
        results.push_back({ root + "dim", 9 });

    else if (iv == std::vector<IT>{ IT::TIERCE_MAJEURE, IT::SIXTE_MINEURE })
        results.push_back({ root + "aug", 9 });

    else
        results.push_back({ root + "?", 1 });

    return results;
}

// ============================================================
// TETRADE
// ============================================================
std::vector<candidate>
analyse_tetrade(const core::Chord& chord)
{
    if (chord.size() != 4)
        throw std::logic_error("analyse_tetrade: chord.size() != 4");

    std::vector<candidate> results;
    const auto& iv = chord.intervals();

    std::string root =
        musical::io::note::formatter::to_string(chord.tonic());

    if (iv == std::vector<IT>{ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE })
        results.push_back({ root + "7", 10 });

    if (iv == std::vector<IT>{ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MAJEURE })
        results.push_back({ root + "7M", 10 });

    if (iv == std::vector<IT>{ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE })
        results.push_back({ root + "m7", 10 });

    if (iv == std::vector<IT>{ IT::TIERCE_MINEURE, IT::TRITON, IT::SEPTIEME_MINEURE })
        results.push_back({ root + "m7b5", 9 });

    if (iv == std::vector<IT>{ IT::TIERCE_MINEURE, IT::TRITON, IT::SIXTE_MAJEURE })
        results.push_back({ root + "dim7", 9 });

    if (iv == std::vector<IT>{ IT::QUARTE_JUSTE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE })
        results.push_back({ root + "7sus4", 8 });

    if (iv == std::vector<IT>{ IT::SECONDE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE })
        results.push_back({ root + "7sus2", 7 });

    return results;
}

} // namespace musical::analysis::chord_name
