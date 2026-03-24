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

// ------------------------------------------------------------
// FIND BY MASK
// ------------------------------------------------------------
std::vector<Diagram>
find_diagrams(IntervalMask mask)
{
    const auto& db = data_movable();

    auto it = db.find(mask);

    if (it == db.end())
        return {};

    return it->second;
}

// ------------------------------------------------------------
// FIND BY MASK + CAGED
// ------------------------------------------------------------
std::vector<Diagram>
find_diagrams(
    IntervalMask mask,
    Diagram::CAGED shape)
{
    std::vector<Diagram> result;

    const auto& db = data_movable();

    auto it = db.find(mask);

    if (it == db.end())
        return result;

    for (const auto& d : it->second)
    {
        if (d.caged() == shape)
            result.push_back(d);
    }

    return result;
}

// ------------------------------------------------------------
// FIND ALL
// ------------------------------------------------------------
std::vector<Diagram>
find_all_diagrams()
{
    std::vector<Diagram> result;

    const auto& db = data_movable();

    for (const auto& [mask, diagrams] : db)
    {
        result.insert(
            result.end(),
            diagrams.begin(),
            diagrams.end()
        );
    }

    return result;
}

// ------------------------------------------------------------
// FIND ALL BY SHAPE
// ------------------------------------------------------------
std::vector<Diagram>
find_all_diagrams(Diagram::CAGED shape)
{
    std::vector<Diagram> result;

    const auto& db = data_movable();

    for (const auto& [mask, diagrams] : db)
    {
        for (const auto& d : diagrams)
        {
            if (d.caged() == shape)
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