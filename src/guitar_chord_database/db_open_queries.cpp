#include <musical/guitar_chord_database/db_open_queries.h>

#include <musical/guitar_chord_database/database_open_a.h>
#include <musical/guitar_chord_database/database_open_c.h>
#include <musical/guitar_chord_database/database_open_d.h>
#include <musical/guitar_chord_database/database_open_e.h>
#include <musical/guitar_chord_database/database_open_g.h>

#include <random>

//#include <iostream> //4 DEBUG
//#include <musical/io/note/output/stream.h> //4 DEBUG

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
// RANDOM CHORDTYPE
// ------------------------------------------------------------
musical::core::chord::ChordType get_random_chord_type()
{
    std::vector<musical::core::chord::ChordType> types;

using chord::database::DiagramMap;        
    auto collect = [&](const DiagramMap& db)
    {
        for (const auto& [type, diagrams] : db)
            types.push_back(type);
    };

    collect(database_open_a());
    collect(database_open_c());
    collect(database_open_d());
    collect(database_open_e());
    collect(database_open_g());

    std::uniform_int_distribution<size_t> dist(0, types.size() - 1);

    return types[dist(rng())];
}
// ------------------------------------------------------------
// RANDOM DIAGRAM
// ------------------------------------------------------------
std::pair<
    musical::core::chord::ChordType,
    OpenChordDiagram
>
get_random_diagram()
{
    using chord::database::DiagramMap;    

    std::vector<
        std::pair<musical::core::chord::ChordType, OpenChordDiagram>
    > diagrams;

    auto collect = [&](const DiagramMap& db)
    {
        for (const auto& [type, vec] : db)
        {
            for (const auto& d : vec)
            {
                diagrams.emplace_back(type, d);
            }
        }
    };

    collect(database_open_a());
    collect(database_open_c());
    collect(database_open_d());
    collect(database_open_e());
    collect(database_open_g());

    std::uniform_int_distribution<size_t> dist(0, diagrams.size() - 1);

    return diagrams[dist(rng())];
}
std::vector<OpenChordDiagram> find_all_positions(
    const musical::core::pitch_t& pitch,
    const musical::core::chord::ChordType& chord_type)
{
    std::vector<OpenChordDiagram> result;

    for(int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<SixStringDiagram::CAGEDShape>(s);

        auto diagrams =
            find_positions(pitch, chord_type, shape);

        result.insert(
            result.end(),
            diagrams.begin(),
            diagrams.end()
        );
    }
    return result;
}


std::vector<OpenChordDiagram> find_positions(
    const musical::core::pitch_t& pitch,
    const musical::core::chord::ChordType& chord_type,
    SixStringDiagram::CAGEDShape shape)
{
    using chord::database::DiagramMap;

    std::vector<OpenChordDiagram> result;

    auto search = [&](const DiagramMap& db)
    {
        for (const auto& [type, diagrams] : db)
        {
            if (type != chord_type)
                continue;

            for (const auto& d : diagrams)
            {
                // std::cout 
                //     << "\nd.root_pitch()=" 
                //     << d.root_pitch() 
                //     << " pitch=" 
                //     <<  pitch << "\n";

                if (d.shape() == shape && 
                    chromatic_index(d.root_pitch()) % 12 ==
                    chromatic_index(pitch) % 12)

                    result.push_back(d);
            }
        }
    };

    search(database_open_a());
    search(database_open_c());
    search(database_open_d());
    search(database_open_e());
    search(database_open_g());

    return result;
}
std::vector<OpenChordDiagram>
find_all_diagrams()
{
    using chord::database::DiagramMap;

    std::vector<OpenChordDiagram> result;

    auto collect = [&](const DiagramMap& db)
    {
        for (const auto& [type, diagrams] : db)
        {
            result.insert(
                result.end(),
                diagrams.begin(),
                diagrams.end()
            );
        }
    };

    collect(database_open_a());
    collect(database_open_c());
    collect(database_open_d());
    collect(database_open_e());
    collect(database_open_g());

    return result;
}
} 