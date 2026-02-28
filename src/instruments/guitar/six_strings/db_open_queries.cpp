
#include <musical/instruments/guitar/six_strings/db_open_queries.h>

#include <musical/instruments/guitar/six_strings/database_open_a.h>
#include <musical/instruments/guitar/six_strings/database_open_c.h>
#include <musical/instruments/guitar/six_strings/database_open_d.h>
#include <musical/instruments/guitar/six_strings/database_open_e.h>
#include <musical/instruments/guitar/six_strings/database_open_g.h>


#include <random>
#include <stdexcept>

namespace musical::instruments::guitar::six_strings::db_open_queries
{

static const DiagramMap& open_database_for_shape(
    SixStringDiagram::CAGEDShape shape)
{
    using SHAPE = SixStringDiagram::CAGEDShape;

    switch (shape)
    {
        case SHAPE::A: return database_open_a();
        case SHAPE::C: return database_open_c();
        case SHAPE::D: return database_open_d();
        case SHAPE::E: return database_open_e();
        case SHAPE::G: return database_open_g();
    }

    throw std::runtime_error("Unknown CAGED shape");
}    

using musical::core::pitch_t;
using musical::core::chord::ChordType;

// ------------------------------------------------------------
// Helper : compare pitch class only
// ------------------------------------------------------------
static bool same_pitch_class(
    const pitch_t& a,
    const pitch_t& b
)
{
    return chromatic_index(a) == chromatic_index(b);
}

std::vector<OpenChordDiagram> find_open_positions(
    const pitch_t& pitch,
    const ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
)
{
    std::vector<OpenChordDiagram> results;

    const auto& db = open_database_for_shape(shape); // base open

    auto it = db.find(chord_type);
    if (it == db.end())
        return results;

    for (const auto& diagram : it->second)
    {
        if (same_pitch_class(diagram.root_pitch(), pitch))
            results.push_back(diagram);
    }

    return results;
}

// ============================================================
// ALL POSITIONS
// ============================================================

std::vector<OpenChordDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape)
{
    std::vector<OpenChordDiagram> results;

    const auto& db = open_database_for_shape(shape);

    for (const auto& [chord_type, diagrams] : db)
    {
        for (const auto& diagram : diagrams)
        {
            results.push_back(diagram);
        }
    }

    return results;
}

// ============================================================
// RANDOM
// ============================================================

// OpenChordDiagram get_random_diagram()
// {
//     static std::mt19937 gen(std::random_device{}());

//     std::uniform_int_distribution<int> shape_dist(0, 4);
//     auto shape = static_cast<SixStringDiagram::CAGEDShape>(shape_dist(gen));

//     const auto& db = database_for_shape(shape);

//     if (db.empty())
//         throw std::runtime_error("Empty database");

//     std::uniform_int_distribution<size_t> chord_dist(0, db.size() - 1);
//     auto chord_it = std::next(db.begin(), chord_dist(gen));

//     const auto& diagrams = chord_it->second;

//     if (diagrams.empty())
//         throw std::runtime_error("No diagrams for selected chord type");

//     std::uniform_int_distribution<size_t> diag_dist(0, diagrams.size() - 1);

//     return diagrams[diag_dist(gen)];
// }

} // namespace musical::instruments::guitar::six_strings::database_queries