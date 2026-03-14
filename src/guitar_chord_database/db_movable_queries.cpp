#include <musical/guitar_chord_database/db_movable_queries.h>

#include <musical/guitar_chord_database/database_movable_a.h> 
#include <musical/guitar_chord_database/database_movable_c.h> 
#include <musical/guitar_chord_database/database_movable_d.h> 
#include <musical/guitar_chord_database/database_movable_e.h> 
#include <musical/guitar_chord_database/database_movable_g.h> 

#include <musical/Core/chord/ChordType.h>

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
// DATABASE SELECTION
// ------------------------------------------------------------
static const MovableDiagramMap&
movable_database_for_shape(SixStringDiagram::CAGEDShape shape)
{
    using SHAPE = SixStringDiagram::CAGEDShape;

    switch (shape)
    {
        case SHAPE::A: return database_movable_a();
        case SHAPE::C: return database_movable_c();
        case SHAPE::D: return database_movable_d();
        case SHAPE::E: return database_movable_e();
        case SHAPE::G: return database_movable_g();
    }

    throw std::runtime_error("Unknown CAGED shape");
}
std::vector<MovableShapeDiagram>
find_all_positions(
    const musical::core::chord::ChordType& chord_type)
{
    std::vector<MovableShapeDiagram> results;

    using SHAPE = SixStringDiagram::CAGEDShape;

    for(int s = 0; s < 5; ++s)
    {
        auto shape = static_cast<SHAPE>(s);

        const auto& db = movable_database_for_shape(shape);

        auto it = db.find(chord_type);

        if(it != db.end())
        {
            results.insert(
                results.end(),
                it->second.begin(),
                it->second.end()
            );
        }
    }

    return results;
}
// ------------------------------------------------------------
// FIND POSITIONS
// ------------------------------------------------------------
std::vector<MovableShapeDiagram>
find_positions(
    const musical::core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape)
{
    const auto& db = movable_database_for_shape(shape);

    auto it = db.find(chord_type);

    if (it == db.end())
        return {};

    return it->second;
}

// ------------------------------------------------------------
// FIND ALL POSITIONS
// ------------------------------------------------------------
std::vector<MovableShapeDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape)
{
    std::vector<MovableShapeDiagram> results;

    const auto& db = movable_database_for_shape(shape);

    for (const auto& [type, diagrams] : db)
    {
        results.insert(results.end(), diagrams.begin(), diagrams.end());
    }

    return results;
}

// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<
    musical::core::chord::ChordType,
    MovableShapeDiagram
>
get_random_diagram()
{
    std::uniform_int_distribution<int> shape_dist(0, 4);

    auto shape =
        static_cast<SixStringDiagram::CAGEDShape>(shape_dist(rng()));

    const auto& db = movable_database_for_shape(shape);

    if (db.empty())
        throw std::runtime_error("Empty movable database");

    std::uniform_int_distribution<size_t>
        chord_dist(0, db.size() - 1);

    auto chord_it =
        std::next(db.begin(), chord_dist(rng()));

    const auto& diagrams = chord_it->second;

    if (diagrams.empty())
        throw std::runtime_error("No movable diagrams for selected chord type");

    std::uniform_int_distribution<size_t>
        diag_dist(0, diagrams.size() - 1);

    return {
        chord_it->first,
        diagrams[diag_dist(rng())]
    };
}
}