#include <command/chord/random_option.h>
#include <command/chord/ChordCommand.h>
#include <command/chord/diagram_layout.h>
#include <terminal.h>

#include <musical/guitar_chord_database/Diagram.h>
#include <musical/guitar_chord_database/open/queries.h>
#include <musical/guitar_chord_database/movable/queries.h>

#include <musical/core/chord/ChordFactory.h>

//#include <musical/io/core/note/out/note_formatter.h>
//#include <musical/io/core/chord/parser/ChordLexer.h>
//#include <musical/io/core/chord/parser/ChordParser.h>

#include <musical/io/guitar/unicode/DiagramRenderer.h>

#include <random>
#include <iostream>

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
            auto [key, diagram] =            
                ::chord::database::queries::open::get_random();

            auto root = musical::core::Pitch(
                    static_cast<uint8_t>(key._root));

            auto chord = musical::core::chord::ChordFactory::create(
                    root,
                    key._mask);

            cmd.chords().push_back(chord);            

            blocks.push_back(io::guitar::unicode::DiagramRenderer::render(diagram));
                                        
        }
        else
        {
            auto [intervals_mask, diagram] =            
                ::chord::database::queries::movable::get_random_diagram();

            std::uniform_int_distribution<int> pitch_dist(0, 11);

            musical::core::Pitch root(pitch_dist(gen));

            auto chord = musical::core::chord::ChordFactory::create(
                    root,
                    intervals_mask);

            cmd.chords().push_back(chord);            
            
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