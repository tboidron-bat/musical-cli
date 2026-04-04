#include <command/chord/diagram_option.h>
#include <command/chord/ChordCommand.h>

#include <musical/core/chord/Chord.h>
#include <musical/core/Tone.h>
#include <musical/chord_db/open/queries.h>
#include <musical/chord_db/movable/queries.h>

#include <sstream>
#include <cstdint>
#include <optional>

namespace cli::chord
{

diagram_option::diagram_option(cli::Command& cmd)
:
cli::command::Option(
    cmd,
    "diagram",
    "d",
    "Show all known guitar chord diagram for the given chord")
{
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "value",
        "If <value> (1–5) is provided, show only that CAGED position",
        command::option::parameter_t::Requirement::OPTIONAL,
        { "1","2","3","4","5" }
    });
}

// ============================================================
// OPEN
// ============================================================
static void add_open_diagrams(
    ChordCommand& cmd,
    const musical::core::chord::Chord& chord,
    std::optional<::chord::db::Diagram::CAGED> caged)
{
    using namespace ::chord::db;

    auto diagrams = queries::open::find_diagrams(
        chord.tone(),
        chord.type().intervals_mask(),
        caged);

    for (const auto& d : diagrams)
    {
        cmd.entries().push_back({
            chord.tone(),
            chord.type().intervals_mask(),
            d
        });
    }
}

// ============================================================
// MOVABLE
// ============================================================
static void add_movable_diagrams(
    ChordCommand& cmd,
    const musical::core::chord::Chord& chord,
    std::optional<::chord::db::Diagram::CAGED> caged)
{
    using namespace ::chord::db;

    auto diagrams = queries::movable::find_diagrams(
        chord.type().intervals_mask(),
        caged);

    for (auto d : diagrams)
    {
        d.place_root(static_cast<uint8_t>(chord.tone()));

        // filtre important
        if (d.base_case() == 0)
            continue;

        cmd.entries().push_back({
            chord.tone(),
            chord.type().intervals_mask(),
            d
        });
    }
}

// ============================================================
// EXECUTE
// ============================================================
int diagram_option::execute() const 
{
    if(!_enabled)
        return EXIT_FAILURE;

    auto& cmd = static_cast<ChordCommand&>(_command_ref);        
    const auto& chords = cmd.parse_chord();    

    if(chords.empty())
    {
        std::cerr << "At least one chord formula is required\n";
        return EXIT_FAILURE;
    }    

    const auto& chord = chords.front();  

    std::optional<::chord::db::Diagram::CAGED> caged;

    if(parameter(0)._provided)
    {
        int v = std::stoi(parameter(0)._value);
        caged = static_cast<::chord::db::Diagram::CAGED>(v);
    }

    cmd.entries().clear();

    add_open_diagrams(cmd, chord, caged);
    add_movable_diagrams(cmd, chord, caged);

    return EXIT_SUCCESS;
}

} // namespace cli::chord


// #include <command/chord/diagram_option.h>
// #include <command/chord/ChordCommand.h>

// #include <musical/core/chord/Chord.h>
// #include <musical/core/Tone.h>
// #include <musical/chord_db/open/queries.h>
// #include <musical/chord_db/movable/queries.h>

// #include <musical/io/core/ToneIO.h>

// #include <terminal.h>
// #include <sstream>
// #include <cstdint>
// #include <optional>

// //#define DEBUG

// namespace cli::chord
// {
// diagram_option::diagram_option(cli::Command&cmd)
// :
// cli::command::Option(
//     cmd,
//     "diagram",
//     "d",
//     "Show all known guitar chord diagram for the given chord")
// {

//     add_parameter({
//         cli::command::option::parameter_t::Type::INT,
//         "value",
//         "If <value> (1–5) is provided, show only that CAGED position",
//         command::option::parameter_t::Requirement::OPTIONAL,
//         { "1","2","3","4","5" }
//     });

//     //TODO
//     // add_parameter({
//     //     cli::command::option::parameter_t::Type::STRING,
//     //     "type",
//     //     "Filter diagrams: open or movable",
//     //     command::option::parameter_t::Requirement::OPTIONAL
//     //     {"open","movable"}
//     //  });

// }
// // ============================================================
// std::vector<::chord::db::Diagram>
// diagram_option::fetch_diagrams(
//     const musical::core::chord::Chord& chord,
//     DiagramSource source,
//     std::optional<::chord::db::Diagram::CAGED> caged) const
// {
//     using namespace ::chord::db;

//     if(source == DiagramSource::Open)
//     {
//         return queries::open::find_diagrams(
//             chord.tone(),
//             chord.type().intervals_mask(),
//             caged);
//     }

//     auto diagrams = queries::movable::find_diagrams(
//         chord.type().intervals_mask(),
//         caged);

//     std::vector<::chord::db::Diagram> result;

//     for (auto diagram : diagrams)
//     {
//         diagram.place_root(static_cast<uint8_t>(chord.tone()));        
//         //FILTRE CRUCIAL pour ne pas faire des diagram open avec 
//         //des diagrams movable

//         if(diagram.base_case() == 0)
//             continue;            

//         result.push_back(diagram);
//     }        
//     return result;
// }
// // ============================================================
// //TODO GERER LES ACCORDS MULTIPLES
// int diagram_option::execute() const 
// {
//     if(!_enabled)
//         return EXIT_FAILURE;

//     auto& cmd = static_cast<ChordCommand&>(_command_ref);        
//     const auto& chords = cmd.parse_chord();    

//     if(chords.empty())
//     {
//         std::cerr << "At least one chord formula is required\n";
//         return EXIT_FAILURE;
//     }    
//     const auto& chord = chords.front();  
    
//     std::optional<::chord::db::Diagram::CAGED> caged;    

//     if(parameter(0)._provided)
//     {

// #ifdef DEBUG
//         std::cout << "parameter(0)._provided" << std::endl;
// #endif
//         int v = std::stoi(parameter(0)._value);
//         caged = static_cast<::chord::db::Diagram::CAGED>(v);
//     }
    
//     cmd.diagrams().clear();                

//     auto open_diagrams = fetch_diagrams(
//         chord,
//         DiagramSource::Open,
//         caged);

//     cmd.diagrams().insert(
//         cmd.diagrams().end(),
//         open_diagrams.begin(),
//         open_diagrams.end());


//     auto movable_diagrams = fetch_diagrams(
//         chord,
//         DiagramSource::Movable,
//         caged);

//     cmd.diagrams().insert(
//         cmd.diagrams().end(),
//         movable_diagrams.begin(),
//         movable_diagrams.end());
 
//     return EXIT_SUCCESS;
// }
// }

