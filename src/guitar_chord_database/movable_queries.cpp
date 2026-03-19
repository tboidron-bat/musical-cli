#include <musical/guitar_chord_database/movable_queries.h>
#include <musical/guitar_chord_database/data_movable.h>

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
// FIND BY TYPE
// ------------------------------------------------------------
std::vector<Diagram>
find_diagrams(const std::string& chord_type_name)
{
    const auto& db = data_movable();

    auto it = db.find(chord_type_name);

    if (it == db.end())
        return {};

    return it->second;
}

// ------------------------------------------------------------
// FIND BY TYPE + CAGED
// ------------------------------------------------------------
std::vector<Diagram>
find_diagrams(
    const std::string& chord_type_name,
    Diagram::CAGED shape)
{
    std::vector<Diagram> result;

    const auto& db = data_movable();

    auto it = db.find(chord_type_name);

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

    for (const auto& [name, diagrams] : db)
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

    for (const auto& [name, diagrams] : db)
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
std::pair<std::string, Diagram>
get_random_diagram()
{
    const auto& db = data_movable();

    if (db.empty())
        throw std::runtime_error("Empty movable database");

    std::uniform_int_distribution<size_t>
        name_dist(0, db.size() - 1);

    auto name_it =
        std::next(db.begin(), name_dist(rng()));

    const auto& diagrams = name_it->second;

    if (diagrams.empty())
        throw std::runtime_error("No diagrams for selected chord");

    std::uniform_int_distribution<size_t>
        diag_dist(0, diagrams.size() - 1);

    return {
        name_it->first,
        diagrams[diag_dist(rng())]
    };
}

} // namespace chord::database::queries::movable