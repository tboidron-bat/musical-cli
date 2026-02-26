#include <musical/instruments/guitar/six_strings/database_queries.h>
#include <musical/instruments/guitar/six_strings/database_by_shape.h>

#include <random>
#include <stdexcept>
#include <iostream> //4 DEBUG
#include <musical/io/note/output/stream.h> //4 DEBUG

namespace guitar::six_strings::chord_diagram::database_queries
{

using namespace musical::instruments::guitar::six_strings;    

// ------------------------------------------------------------
// Internal helper
// ------------------------------------------------------------
static bool matches_position_kind(
    const ChordDiagram& diagram,
    PositionKind kind
)
{
    switch (kind)
    {
        case PositionKind::OPEN:
            return diagram.is_open_chord();

        case PositionKind::MOVABLE:
            return !diagram.is_open_chord();

        case PositionKind::ALL:
            return true;
    }

    return false;
}


// ------------------------------------------------------------
// Generic finder
// ------------------------------------------------------------
std::vector<ChordDiagram> find_positions(
    const musical::core::pitch_t pitch,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape,
    PositionKind kind
)
{
    std::vector<ChordDiagram> results;

    const auto& db = database_for_shape(shape);


    //std::cout << "  DB size   : " << db.size() << " chord types\n";    

    auto it = db.find(chord_type);

    if (it == db.end())
    {
        std::cout << "  → No entry for this chord type\n";
        return results;
    }

    // std::cout << "  → Chord type found. "
    //         << it->second.size()
    //         << " diagram(s) stored\n";

    const auto& diagrams = it->second;

    for (const auto& diagram : diagrams)
    {
        //std::cout << "    Checking diagram... " << std::endl; //4 DEBUG

        if (!matches_position_kind(diagram, kind))
        {
            //std::cout << "rejected (position kind)\n";
            continue;
        }

        if (chromatic_index(diagram.root_pitch()) !=
            chromatic_index(pitch))
        {
            // std::cout << "rejected (root mismatch: "
            //         << diagram.root_pitch()
            //         << ")\n";
            continue;
        }
        //std::cout << "accepted\n";
        results.push_back(diagram);
    }
    return results;
}


// ------------------------------------------------------------
// Open only
// ------------------------------------------------------------
std::vector<ChordDiagram> find_open_position(
    const musical::core::pitch_t pitch,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape
)
{
    return find_positions(
        pitch,
        chord_type,
        shape,
        PositionKind::OPEN
    );
}


// ------------------------------------------------------------
// Movable only (future transposition system)
// ------------------------------------------------------------
std::vector<ChordDiagram> find_movable_position(
    const musical::core::pitch_t pitch,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape
)
{
    return find_positions(
        pitch,
        chord_type,
        shape,
        PositionKind::MOVABLE
    );
}


// ------------------------------------------------------------
// Random diagram
// ------------------------------------------------------------
ChordDiagram get_random_diagram()
{
    using SHAPE = ChordDiagram::CAGEDShape;

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> shape_dist(0, 4);

    auto shape = static_cast<SHAPE>(shape_dist(gen));

    const auto& db = database_for_shape(shape);

    if (db.empty())
        throw std::runtime_error("Empty database");

    std::uniform_int_distribution<size_t> chord_dist(0, db.size() - 1);
    auto chord_it = std::next(db.begin(), chord_dist(gen));

    const auto& diagrams = chord_it->second;

    if (diagrams.empty())
        throw std::runtime_error("No diagrams for selected chord type");

    std::uniform_int_distribution<size_t> diag_dist(0, diagrams.size() - 1);

    return diagrams[diag_dist(gen)];
}

} // namespace musical::instruments::guitar::six_strings