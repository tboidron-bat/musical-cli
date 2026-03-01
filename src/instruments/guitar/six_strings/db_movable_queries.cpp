#include <musical/instruments/guitar/six_strings/db_movable_queries.h>

#include <musical/instruments/guitar/six_strings/database_movable_a.h> 
#include <musical/instruments/guitar/six_strings/database_movable_c.h> 
#include <musical/instruments/guitar/six_strings/database_movable_d.h> 
#include <musical/instruments/guitar/six_strings/database_movable_e.h> 
#include <musical/instruments/guitar/six_strings/database_movable_g.h> 

#include <musical/Core/chord/ChordType.h>

#include <stdexcept>
#include <random>

namespace musical::instruments::guitar::six_strings::db_movable_queries
{
static const MovableDiagramMap& movable_database_for_shape(
    SixStringDiagram::CAGEDShape shape)
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
std::vector<MovableShapeDiagram> find_movable_positions
    (
    const core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
    )
{
    const auto& db = movable_database_for_shape(shape);

    auto it = db.find(chord_type);
    if (it == db.end())
        return {};

    return it->second;
}

std::vector<MovableShapeDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape)
{
    std::vector<MovableShapeDiagram> results;

    const auto& db = movable_database_for_shape(shape);

    for (const auto& [chord_type, diagrams] : db)
    {
        for (const auto& diagram : diagrams)
        {
            results.push_back(diagram);
        }
    }

    return results;


    return results;
}

MovableShapeDiagram get_random_diagram()
{
    static std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<int> shape_dist(0, 4);
    auto shape =
        static_cast<SixStringDiagram::CAGEDShape>(shape_dist(gen));

    const auto& db = movable_database_for_shape(shape);  

    if (db.empty())
        throw std::runtime_error("Empty database");

    std::uniform_int_distribution<size_t>
        chord_dist(0, db.size() - 1);

    auto chord_it =
        std::next(db.begin(), chord_dist(gen));

    const auto& diagrams = chord_it->second;

    if (diagrams.empty())
        throw std::runtime_error("No movable diagrams for selected chord type");

    std::uniform_int_distribution<size_t>
        diag_dist(0, diagrams.size() - 1);

    return diagrams[diag_dist(gen)];
}



}