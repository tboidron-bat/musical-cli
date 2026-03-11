#include <command/chord/ChordCommand.h>
#include <CommandOption.h>
#include <stream_option.h>

#include <command/chord/version_option.h>
#include <command/chord/help_option.h>
#include <command/chord/diagram_option.h>
#include <command/chord/random_option.h>
#include <command/chord/dumpdb_option.h>
#include <command/chord/play_option.h>
#include <command/chord/difficulty_option.h>
#include <command/chord/tuning_option.h>


#include <musical/io/guitar/diagram/unicode/Grid.h>

#include <musical/io/chord/input/ChordLexer.h>
#include <musical/io/chord/input/ChordParser.h>
#include <musical/io/chord/output/stream.h>

#include <sstream>

//#define CHORD_COMMAND_DEBUG

namespace cli::chord
{
ChordCommand::ChordCommand()
{
    //atention l'ordre d'ajout à une importance.
    _options.emplace_back(std::make_unique<version_option>(this));      
    _options.emplace_back(std::make_unique<help_option>(this));  
    _options.emplace_back(std::make_unique<random_option>(this));
    _options.emplace_back(std::make_unique<dumpdb_option>(this));    
    _options.emplace_back(std::make_unique<diagram_option>(this));          
    _options.emplace_back(std::make_unique<play_option>(this));
    _options.emplace_back(std::make_unique<difficulty_option>(this));
    _options.emplace_back(std::make_unique<tuning_option>(this));
}
int ChordCommand::run(int argc, char** argv)
{
    if(argc < 2)
    {
        print_usage();
        return 1;
    }

    for (auto& opt : _options)
        opt->parse(argc, argv);

    if(_options[OptionId::VERSION]->execute())
        return EXIT_SUCCESS;    
    
    if(_options[OptionId::HELP]->execute())
        return EXIT_SUCCESS;

    if(_options[OptionId::DUMPDB]->execute())
        return EXIT_SUCCESS;

    if(_options[OptionId::RANDOM]->execute())
    {
        //TODO cette fonction devrait plutot
        //charger un chord dans _chord
        //plutot que de trouver un diagram
        //au hasard dans les bases de donnees.
    }
    else
    {
        std::string symbol;

        for(int i = 1; i < argc; ++i)
        {
            if(argv[i][0] != '-')
            {
                symbol = argv[i];
                break;
            }
        }

        if(symbol.empty())
        {
            std::cerr << "Chord symbol required\n";
            return 1;
        }

        _chord = parse_chord(symbol);    

        if(!_chord)
        {
            std::cerr << "Invalid chord symbol\n";
            return 1;
        }
    }
    std::cout << *_chord << "\n";    

    _options[OptionId::DIAGRAM]->execute();
    _options[OptionId::PLAY]->execute();

    return EXIT_SUCCESS;
}
std::optional<musical::core::chord::Chord>
ChordCommand::parse_chord(const std::string& symbol)
{
    using namespace musical::io::chord;

#ifdef CHORD_COMMAND_DEBUG
    std::cout << "ChordCommand::parse_chord(...) input=" << symbol << "\n";    
#endif

    auto tokens = ChordLexer::tokenize(symbol);

    auto chord_opt = ChordParser::parse(tokens);

    return chord_opt;
}
void ChordCommand::print_name() const
{
    std::cout << "Chord CLI — version 0.3.0";
}
void ChordCommand::print_usage() const 
{
    std::cout << "Usage:\n";
    std::cout << "\tchord [options] <symbol>\n";
    std::cout << "Try:\n";
    std::cout << "\tchord --help\n";
}        

void ChordCommand::print_help() const
{
    std::cout << "Options:\n";

    for (const auto& opt : _options)
        std::cout << *opt;
}
} // namespace cli::chord