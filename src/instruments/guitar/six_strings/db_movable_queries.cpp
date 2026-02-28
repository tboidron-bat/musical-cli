#include <musical/instruments/guitar/six_strings/db_movable_queries.h>

#include <musical/instruments/guitar/six_strings/database_movable_a.h> // TODO : dispatcher selon shape

#include <musical/Core/chord/ChordType.h>

namespace musical::instruments::guitar::six_strings::db_movable_queries
{


std::vector<MovableShapeDiagram> find_movable_positions(
    const core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape
)
{
    std::vector<MovableShapeDiagram> results;

    const auto& db = database_movable_a(); // TODO : dispatcher selon shape

    auto it = db.find(chord_type);
    if (it == db.end())
        return results;

    for (const auto& movable : it->second)
    {
    }

    return results;
}

std::vector<MovableShapeDiagram>
find_all_positions(SixStringDiagram::CAGEDShape shape)
{
    std::vector<MovableShapeDiagram> results;

    return results;
}


}