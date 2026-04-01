#include <command/chord/diagram_option.h>
#include <command/chord/diagram_layout.h>
#include <command/chord/ChordCommand.h>

#include <musical/core/chord/Chord.h>
#include <musical/core/Tone.h>
#include <musical/guitar_chord_database/open/queries.h>
#include <musical/guitar_chord_database/movable/queries.h>
#include <musical/io/core/chord/out/naming.h>
#include <musical/io/core/ToneIO.h>
//#include <musical/io/core/chord/ChordIO.h>
#include <musical/io/guitar/unicode/DiagramRenderer.h>

#include <terminal.h>
//#include <iostream>
#include <sstream>
#include <cstdint>
#include <optional>

//#define DEBUG

namespace cli::chord
{
diagram_option::diagram_option(cli::Command&cmd)
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

    //TODO
    // add_parameter({
    //     cli::command::option::parameter_t::Type::STRING,
    //     "type",
    //     "Filter diagrams: open or movable",
    //     command::option::parameter_t::Requirement::OPTIONAL
    //     {"open","movable"}
    //  });

}
// ============================================================
static std::string make_name(const musical::core::chord::Chord& chord)
{
    std::ostringstream oss;
    oss << chord.tone();
    return oss.str() + musical::io::chord::to_string(chord.type());
}
// ============================================================
std::vector<::chord::database::Diagram>
diagram_option::fetch_diagrams(
    const musical::core::chord::Chord& chord,
    DiagramSource source,
    std::optional<::chord::database::Diagram::CAGED> caged) const
{
    using namespace ::chord::database;

    if(source == DiagramSource::Open)
    {
        return queries::open::find_diagrams(
            chord.tone(),
            chord.type().intervals_mask(),
            caged
        );
    }

    return queries::movable::find_diagrams(
        chord.type().intervals_mask(),
        caged
    );
}
// ============================================================
void diagram_option::render(
    const std::vector<::chord::database::Diagram>& diagrams,
    const musical::core::chord::Chord& chord,
    DiagramSource source) const
{
    std::vector<std::string> blocks;   

    std::string name = make_name(chord);

    for (auto diagram : diagrams)
    {
        if(source == DiagramSource::Movable)
        {
            diagram.place_root(static_cast<uint8_t>(chord.tone()));
            //FILTRE CRUCIAL pour ne pas faire des diagram open avec 
            //des diagrams movable
            if(diagram.base_case() == 0)
                continue;            
        }            
        blocks.push_back(
            io::guitar::unicode::DiagramRenderer::render(diagram,name));
    }            

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();
}
// ============================================================
//TODO GERER LES ACCORDS MULTIPLES
int diagram_option::execute() const 
{
    if(!_enabled)
        return EXIT_FAILURE;

    auto& cmd = static_cast<ChordCommand&>(_command_ref);        
    const auto& chords = cmd.chords();    

    if(chords.empty())
    {
        std::cerr << "At least one chord formula is required\n";
        return EXIT_FAILURE;
    }    
    const auto& chord = chords.front();  
    
    std::optional<::chord::database::Diagram::CAGED> caged;    

    if(parameter(0)._provided)
    {

#ifdef DEBUG
        std::cout << "parameter(0)._provided" << std::endl;
#endif
        int v = std::stoi(parameter(0)._value);
        caged = static_cast<::chord::database::Diagram::CAGED>(v);
    }

    auto open_diagrams = fetch_diagrams(
        chord,
        DiagramSource::Open,
        caged);

    auto movable_diagrams = fetch_diagrams(
        chord,
        DiagramSource::Movable,
        caged);

    render(open_diagrams, chord, DiagramSource::Open);
    render(movable_diagrams, chord, DiagramSource::Movable);
    
    return EXIT_SUCCESS;
}
}

