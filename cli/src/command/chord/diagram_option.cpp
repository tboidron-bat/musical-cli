#include <command/chord/diagram_option.h>
#include <command/chord/diagram_layout.h>
#include <command/chord/ChordCommand.h>

#include <musical/io/guitar/unicode/OpenDiagram.h>
#include <musical/io/guitar/unicode/MovableDiagram.h>

#include <musical/guitar_chord_database/db_open_queries.h>
#include <musical/guitar_chord_database/db_movable_queries.h>

#include <musical/io/guitar/stream.h>

//#include <musical/io/guitar/ascii/stream_diagram.h>

#include <terminal.h>
#include <iostream>

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
void diagram_option::render(
    const musical::core::chord::Chord& chord,    
    const std::vector<::chord::database::MovableShapeDiagram>& diagrams) const
{
    std::vector<std::string> blocks;       

    for(auto diagram : diagrams)
    {
        diagram.place_root(chord.root());               
        blocks.push_back(
            io::guitar::unicode::MovableDiagram(diagram).render()
        );
    }

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();
}
void diagram_option::render(const std::vector<::chord::database::OpenChordDiagram>& diagrams) const
{
    std::vector<std::string> blocks;   

    for (const auto& diagram : diagrams)
        blocks.push_back(
            io::guitar::unicode::OpenDiagram(diagram).render());

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();
}
//std::vector<::chord::database::SixStringDiagram>
void
diagram_option::find_all(const musical::core::chord::Chord&chord) const
{
#ifdef DEBUG
for(auto i : chord.type().intervals())
    std::cout << static_cast<int>(i) << " ";
#endif

    std::vector<::chord::database::OpenChordDiagram> open_diagrams =
        ::chord::database::queries::open::find_all_positions(
            chord.root(),
            chord.type()
        );   

#ifdef DEBUG
    std::cout << '[' << __func__ << ']'
#endif

    std::cout 
        << "find " << open_diagrams.size() << " open(s) diagram(s)."
        << std::endl;

    render(open_diagrams);        

    std::vector<::chord::database::MovableShapeDiagram> movable_diagrams =
        ::chord::database::queries::movable::find_all_positions(
            chord.type()
        );   

#ifdef DEBUG
    std::cout << '[' << __func__ << ']'
#endif

    std::cout 
        << "find " << movable_diagrams.size() << " movable(s) diagram(s)."
        << std::endl;

    render(chord, movable_diagrams);                    
}
//std::vector<::chord::database::SixStringDiagram> 
void
diagram_option::find_caged(
    const musical::core::chord::Chord&chord,
    ::chord::database::SixStringDiagram::CAGEDShape filter) const
{
    auto open_diagrams = 
        ::chord::database::queries::open::find_positions(
            chord.root(),
            chord.type(),
            filter
        );            

    render(open_diagrams);        

    auto movable_diagrams = ::chord::database::queries::movable::find_positions(
            chord.type(),
            filter);

    render(chord,movable_diagrams);                                
}
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

    if(parameter(0)._provided)
    {

#ifdef DEBUG
        std::cout << "parameter(0)._provided" << std::endl;
#endif
        int caged = std::stoi(parameter(0)._value);
        find_caged(chord,static_cast<::chord::database::SixStringDiagram::CAGEDShape>(caged));
    }
    else
        find_all(chord);

    // if(blocks.empty())
    // {
    //     std::cerr << "No diagram found for this chord formula\n";
    //     return EXIT_FAILURE;
    // }

    
    return EXIT_SUCCESS;
}
}

