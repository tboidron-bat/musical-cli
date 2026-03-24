#include <command/chord/diagram_option.h>
#include <command/chord/diagram_layout.h>
#include <command/chord/ChordCommand.h>


#include <musical/analysis/chord/io.h>
#include <musical/io/guitar/unicode/DiagramRenderer.h>

#include <musical/guitar_chord_database/open_queries.h>
#include <musical/guitar_chord_database/movable_queries.h>
#include <musical/io/guitar/stream.h>

#include <musical/io/note/out/note_formatter.h>

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
    const std::vector<::chord::database::Diagram>& diagrams) const
{
    std::vector<std::string> blocks;       

    for(auto diagram : diagrams)
    {
        diagram.place_root(
            chromatic_index(chord.root()) % 12);               

        //FILTRE CRUCIAL pour ne pas faire des diagram open avec 
        //des diagrams movable
        if (diagram.base_case() == 0)
            continue;            

        blocks.push_back(
             io::guitar::unicode::DiagramRenderer::render(diagram)
        );
    }

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();
}
void diagram_option::render(
    const std::vector<::chord::database::Diagram>& diagrams) const
{
    std::vector<std::string> blocks;   

    for (const auto& diagram : diagrams)
        blocks.push_back(
            io::guitar::unicode::DiagramRenderer::render(diagram));

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();
}
void
diagram_option::find_all(const musical::core::chord::Chord&chord) const
{
#ifdef DEBUG
for(auto i : chord.type().intervals())
    std::cout << static_cast<int>(i) << " ";
#endif

    //analyser le chord.type() pour en tirer le nom
    std::string type_name = 
        musical::analysis::chord::find_name(chord.type());

    std::string full_name =
        musical::io::note::formatter::to_string(chord.root()) + ":" + type_name;        

    std::vector<::chord::database::Diagram> open_diagrams =
        ::chord::database::queries::open::find_all_positions(
            full_name);   

#ifdef DEBUG
    std::cout << '[' << __func__ << "] chord name = " << full_name
        << "find " << open_diagrams.size() << " open(s) diagram(s)."
        << std::endl;
#endif

    std::cout << "Open diagram:\n";

    render(open_diagrams);  
    
    auto movable_diagrams = ::chord::database::queries::movable::find_diagrams(type_name); 
        
#ifdef DEBUG
    std::cout << '[' << __func__ << ']';
#endif

    std::cout 
        << "Movable diagram:"
        << std::endl;

    render(chord, movable_diagrams);                    
}
void
diagram_option::find_caged(
    const musical::core::chord::Chord&chord,
    ::chord::database::Diagram::CAGED filter) const
{
    std::string name = 
        musical::analysis::chord::find_name(chord.type());


    auto open_diagrams = 
        ::chord::database::queries::open::find_positions(
            chord.root(),
            name,
            filter
        );            

    render(open_diagrams);        

    auto movable_diagrams = ::chord::database::queries::movable::find_diagrams(
            name,
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
        find_caged(chord,static_cast<::chord::database::Diagram::CAGED>(caged));
    }
    else
        find_all(chord);
    
    return EXIT_SUCCESS;
}
}

