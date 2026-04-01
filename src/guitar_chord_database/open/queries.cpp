#include <musical/guitar_chord_database/open/queries.h>
#include <musical/guitar_chord_database/open/database.h>

#include <random>
#include <stdexcept>

//#include <iostream> 
//#define DEBUG

namespace chord::database::queries::open
{
// ============================================================
// RNG
// ============================================================
static std::mt19937& rng()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}
// ============================================================
std::vector<Diagram>
find_diagrams(
    Tone root,
    IntervalMask mask,
    std::optional<Diagram::CAGED> shape)
{
    const auto& db = data_open();

    key_t key{ root, mask };

    auto it = db.find(key);

    if (it == db.end())
        return {};

    const auto& diagrams = it->second;

    // 🚀 cas sans filtre → retour direct (zero copie inutile si NRVO/move)
    if(!shape)
        return diagrams;

  // 🔍 cas avec filtre
    std::vector<Diagram> result;
    result.reserve(diagrams.size()); // micro-opt

    for (const auto& d : diagrams)
    {
        if (d.caged() == *shape)
            result.push_back(d);
    }

    return result;
}
// ============================================================
std::vector<Diagram>
find_all_diagrams(
    std::optional<IntervalMask> mask)
{
    std::vector<Diagram> result;

    const auto& db = data_open();

    for (const auto& [key, diagrams] : db)
    {
        if(mask && key._mask != *mask)
            continue;

        result.insert(result.end(), diagrams.begin(), diagrams.end());
    }

    return result;
}
// ------------------------------------------------------------
// RANDOM CHORD
// ------------------------------------------------------------
std::pair<key_t, Diagram>
get_random()
{
    const auto& db = data_open();

    if (db.empty())
        throw std::runtime_error("Empty open database");

    std::uniform_int_distribution<size_t> chord_dist(0, db.size() - 1);
    auto chord_it = std::next(db.begin(), chord_dist(rng()));

    const auto& diagrams = chord_it->second;

    if (diagrams.empty())
        throw std::runtime_error("No diagrams for selected chord");

    std::uniform_int_distribution<size_t> diag_dist(0, diagrams.size() - 1);

    return {
        chord_it->first,
        diagrams[diag_dist(rng())]
    };
}

} // namespace chord::database::queries::open