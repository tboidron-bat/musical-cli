#include <command/chord/diagram_option.h>
#include <command/chord/diagram_layout.h>
#include <command/chord/ChordCommand.h>

#include <musical/Core/chord/Chord.h>
#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/io/guitar/stream.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/guitar/stream_diagram.h>
//#include <musical/io/guitar/stream_diagram2.h>
#include <musical/io/guitar/diagram/unicode/Movable.h>

#include <terminal.h>
#include <iostream>

namespace cli::chord
{
diagram_option::diagram_option(cli::Command*cmd)
:
cli::command::Option(
    cmd,
    "diagram",
    "d",
    "Show chord diagram")
{

    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "value",
        "If <value> (1–5) is provided, show only that CAGED position",
        command::option::parameter_t::Requirement::OPTIONAL});

    //accepted value:
    //std::vector<std::string>{ "1","2","3","4","5" }

    //TODO
    //ajouter un parametre open/movable
}
int diagram_option::execute() const 
{
    using musical::instruments::guitar::six_strings::OpenChordDiagram;

    if(!_enabled)
        return 0;

    auto width = terminal::get_width();    
    bool found = false;
    std::vector<std::string> blocks;   
    
    const ChordCommand* cmd =
        static_cast<const ChordCommand*>(_command);

    const auto& chord_opt = cmd->chord();

    if(!chord_opt)
    {
        std::cerr << "Chord required\n";
        return 1;
    }
    const auto& chord = *chord_opt;


    //CAGED
    int start = 0;
    int end = 5;

    if(get_parameter(0)._provided)
    {
        int i = std::stoi(get_parameter(0)._value);

        if(i < 1 || i > 5)
        {
            std::cerr << "CAGED position must be between 1 and 5\n";
            return 1;
        }

        start = i - 1;
        end = i;
    }


    for(int s = start; s < end; ++s)
    {
        auto shape =
            static_cast<OpenChordDiagram::CAGEDShape>(s);
        const auto open_diagrams =
            musical::instruments::guitar::six_strings::db_open_queries::find_open_positions(
                chord.root(),
                chord.type(),
                shape
            );
        for (const auto& diagram : open_diagrams)
        {
            std::ostringstream oss;
            oss << diagram;
            blocks.push_back(oss.str());
            found = true;
        }
        auto movable_diagrams =
            musical::instruments::guitar::six_strings::db_movable_queries::find_movable_positions(
                chord.type(),
                shape
            );
        for (auto& diagram : movable_diagrams)
        {
            diagram.place_root(chord.root());   
                
            blocks.push_back(
                io::guitar::diagram::unicode::Movable(diagram).render()
            );
            found = true;                
        }
    }
    std::cout << layout_blocks(blocks, width);
    
    if (!found)
    {
        std::cerr << "No diagram found for this chord formula\n";
        return 1;
    }
    return 1;
}
}

