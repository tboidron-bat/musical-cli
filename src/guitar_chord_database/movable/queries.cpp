#include <musical/guitar_chord_database/movable/queries.h>
#include <musical/guitar_chord_database/movable/database.h>

#include <stdexcept>
#include <random>
#include <iterator>

namespace chord::database::queries::movable
{

// ------------------------------------------------------------
// RNG
// ------------------------------------------------------------
static std::mt19937& rng()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}
// ============================================================
std::vector<Diagram>
find_diagrams(
    IntervalMask mask,
    std::optional<Diagram::CAGED> shape)
{
    const auto& db = data_movable();

    auto it = db.find(mask);

    if (it == db.end())
        return {};

    const auto& diagrams = it->second;

    // 🚀 pas de filtre → retour direct
    if(!shape)
        return diagrams;

    // 🔍 filtre CAGED
    std::vector<Diagram> result;
    result.reserve(diagrams.size());

    for (const auto& d : diagrams)
    {
        if (d.caged() == *shape)
            result.push_back(d);
    }

    return result;
}
// ============================================================
std::vector<Diagram>
find_all_diagrams(std::optional<Diagram::CAGED> shape)
{
    std::vector<Diagram> result;

    const auto& db = data_movable();

    for (const auto& [mask, diagrams] : db)
    {
        // 🚀 pas de filtre → insertion directe
        if(!shape)
        {
            result.insert(
                result.end(),
                diagrams.begin(),
                diagrams.end()
            );
            continue;
        }

        // 🔍 filtre
        for (const auto& d : diagrams)
        {
            if (d.caged() == *shape)
                result.push_back(d);
        }
    }

    return result;
}
// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<IntervalMask, Diagram>
get_random_diagram()
{
    const auto& db = data_movable();

    if (db.empty())
        throw std::runtime_error("Empty movable database");

    std::uniform_int_distribution<size_t>
        mask_dist(0, db.size() - 1);

    auto it =
        std::next(db.begin(), mask_dist(rng()));

    const auto& diagrams = it->second;

    if (diagrams.empty())
        throw std::runtime_error("No diagrams for selected chord");

    std::uniform_int_distribution<size_t>
        diag_dist(0, diagrams.size() - 1);

    return {
        it->first,
        diagrams[diag_dist(rng())]
    };
}

} // namespace chord::database::queries::movable