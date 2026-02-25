#include <musical/instruments/guitar/six_strings/database_queries.h>
#include <musical/instruments/guitar/six_strings/database_by_shape.h>

#include <random>
#include <stdexcept>

namespace musical::instruments::guitar::six_strings
{

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
    const musical::core::pitch_t /*pitch*/,
    const musical::core::chord::ChordType& chord_type,
    ChordDiagram::CAGEDShape shape,
    PositionKind kind
)
{
    std::vector<ChordDiagram> results;

    const auto& db = database_for_shape(shape);

    auto it = db.find(chord_type);

    if (it == db.end())
        return results;

    const auto& diagrams = it->second;

    for (const auto& diagram : diagrams)
    {
        if (!matches_position_kind(diagram, kind))
            continue;

        // ⚠️ TODO:
        // Ici il faudra vérifier que la tonique réelle du diagramme
        // correspond au pitch demandé.
        //
        // Pour l’instant ta base ne contient que les formes ouvertes
        // correspondant au pitch naturel de la forme.

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