#include <musical/guitar_chord_database/open/queries.h>
#include <musical/guitar_chord_database/open/database.h>

#include <random>
#include <stdexcept>

namespace chord::database::queries::open
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
// RANDOM CHORD NAME
// ------------------------------------------------------------
std::string get_random_chord_name()
{
    const auto& db = database_open();

    if (db.empty())
        throw std::runtime_error("Empty open database");

    std::uniform_int_distribution<size_t> dist(0, db.size() - 1);

    auto it = std::next(db.begin(), dist(rng()));

    return it->first;
}

// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<std::string, Diagram>
get_random_diagram()
{
    const auto& db = database_open();

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

// ------------------------------------------------------------
// FIND POSITIONS (pitch + chord_name)
// ------------------------------------------------------------
std::vector<Diagram>
find_positions(
    const musical::core::pitch_t& pitch,
    const std::string& chord_name)
{
    return find_positions(pitch, chord_name, Diagram::CAGED::A); // fallback optionnel
}

// ------------------------------------------------------------
// FIND POSITIONS (pitch + chord_name + shape)
// ------------------------------------------------------------
std::vector<Diagram>
find_positions(
    const musical::core::pitch_t& pitch,
    const std::string& chord_name,
    Diagram::CAGED shape)
{
    std::vector<Diagram> result;

    const auto& db = database_open();

    auto it = db.find(chord_name);

    if (it == db.end())
        return result;

    for (const auto& d : it->second)
    {
        // TODO : quand tu remettras root_pitch dans Diagram
        // pour l'instant on filtre uniquement par shape

        if (d.caged() == shape)
            result.push_back(d);
    }

    return result;
}

// ------------------------------------------------------------
// FIND ALL POSITIONS (pitch + chord_name)
// ------------------------------------------------------------
std::vector<Diagram>
find_all_positions(const std::string& chord_name)
{
    const auto& db = database_open();

    auto it = db.find(chord_name);

    if (it == db.end())
        return {};

    return it->second;
}

// ------------------------------------------------------------
// FIND ALL DIAGRAMS
// ------------------------------------------------------------
std::vector<Diagram>
find_all_diagrams()
{
    std::vector<Diagram> result;

    const auto& db = database_open();

    for (const auto& [name, diagrams] : db)
    {
        result.insert(result.end(), diagrams.begin(), diagrams.end());
    }

    return result;
}

} // namespace chord::database::queries::open