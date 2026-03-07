#include <chord/diagram_option.h>
#include <terminal.h>
#include <chord/diagram_layout.h>
#include <chord/ChordCommand.h>

#include <musical/Core/chord/Chord.h>
#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/io/instruments/guitar/six_strings/stream.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/instruments/guitar/six_strings/stream_diagram.h>
#include <musical/io/instruments/guitar/six_strings/movable_shape_diagram_to_ascii.h>

#include <iostream>

namespace cli::chord
{
diagram_option::diagram_option(cli::Command*cmd)
:
cli::command::option(cmd,"diagram","d","Show chord diagram")
{

    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "position",
        "CAGED position (1–5)"});
    //std::vector<std::string>{ "1","2","3","4","5" }            
}
int diagram_option::execute() const 
{
    using musical::instruments::guitar::six_strings::OpenChordDiagram;
    int position = -1;

    if(has_parameter("position"))
    {
        position = parameter_value_int("position");
    }

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

    for(int s = 0; s < 5; ++s)
    {
        if (position != -1 && s != position - 1)
            continue;
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
                io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
            );
            found = true;                
        }
    }
    std::cout
        << cli::chord::layout_ascii_blocks(blocks, width);
    if (!found)
    {
        std::cerr << "No diagram found for this chord formula\n";
        return 1;
    }
    return 0;
}
}

        //     "--diagram",
        //     "-d",
        //     "Show chord diagram.\n"
        //     "If <value> (1–5) is provided, show only that CAGED position.",
        //     true,
        //     true,
        //     1,
        //     std::vector<std::string>{ "1","2","3","4","5" }
