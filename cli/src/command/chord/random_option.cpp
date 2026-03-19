#include <command/chord/random_option.h>
#include <command/chord/ChordCommand.h>
#include <command/chord/diagram_layout.h>
#include <terminal.h>

#include <musical/guitar_chord_database/Diagram.h>
#include <musical/guitar_chord_database/open_queries.h>
#include <musical/guitar_chord_database/movable_queries.h>

#include <musical/io/note/out/note_formatter.h>
#include <musical/io/chord/in/ChordLexer.h>
#include <musical/io/chord/in/ChordParser.h>

#include <musical/io/guitar/unicode/DiagramRenderer.h>

#include <random>
#include <iostream>

#include <musical/io/chord/out/stream.h> //DEBUG

namespace cli::chord
{
random_option::random_option(cli::Command&cmd)
:
command::Option(cmd,"random","r","Show a completely random chord")
{    
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "value",
        "If provided, generate <value> random chords",
        command::option::parameter_t::Requirement::OPTIONAL
        });
}
int random_option::execute() const
{
    if(!_enabled)
        return 0;

    int count = 1;        

    if(parameter(0)._provided)
        count = std::stoi(parameter(0)._value);

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    auto& cmd = static_cast<ChordCommand&>(_command_ref);      
    
    std::vector<std::string> blocks;       
    
    while(count)
    {
        const bool choose_open = dist(gen) == 0;

        if(choose_open)
        {
            auto [type, diagram] =            
                ::chord::database::queries::open::get_random_diagram();

            auto tokens = musical::io::chord::ChordLexer::tokenize(type);
            auto chord_opt = musical::io::chord::ChordParser::parse(tokens);

            if (chord_opt)
                cmd.chords().push_back(*chord_opt);

            blocks.push_back(io::guitar::unicode::DiagramRenderer::render(diagram));
                                        
        }
        else
        {
            auto [type, diagram] =            
                ::chord::database::queries::movable::get_random_diagram();

            std::uniform_int_distribution<int> pitch_dist(0, 11);

            musical::core::pitch_t root =
                musical::core::pitch_from_chromatic_index(pitch_dist(gen));

            std::string symbol =
                musical::io::note::formatter::to_string(root)
                + type;

            auto tokens = musical::io::chord::ChordLexer::tokenize(symbol);
            auto chord_opt = musical::io::chord::ChordParser::parse(tokens);

            if (chord_opt)
                cmd.chords().push_back(*chord_opt);            
            
            blocks.push_back(
                io::guitar::unicode::DiagramRenderer::render(diagram));

        }        
        count--;
    }      

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();    

    return EXIT_SUCCESS;
}

}