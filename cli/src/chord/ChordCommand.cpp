#include <chord/ChordCommand.h>
#include <command_option.h>

#include <chord/help_option.h>
#include <chord/diagram_option.h>
#include <chord/random_option.h>
#include <chord/dumpdb_option.h>
#include <chord/play_option.h>
#include <chord/difficulty_option.h>
#include <chord/tuning_option.h>

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
    _options.emplace_back(std::make_unique<help_option>(this));  
    _options.emplace_back(std::make_unique<diagram_option>(this));      
    _options.emplace_back(std::make_unique<random_option>(this));
    _options.emplace_back(std::make_unique<play_option>(this));
    _options.emplace_back(std::make_unique<dumpdb_option>(this));
    _options.emplace_back(std::make_unique<difficulty_option>(this));
    _options.emplace_back(std::make_unique<tuning_option>(this));
}
int ChordCommand::run(int argc, char** argv)
{
    if(argc < 2)
    {
        print_help();
        return 1;
    }

    // ------------------------------------------------------------
    // 1️⃣ Si le premier argument n'est pas une option → chord
    // ------------------------------------------------------------
    std::string_view first = argv[1];

    int option_start = 1;

    if(!first.starts_with("-"))
    {
        _chord = parse_chord(argv[1]);

        if(!_chord)
        {
            std::cerr << "Invalid chord symbol\n";
            return 1;
        }

        option_start = 2;
    }    


    
    // ------------------------------------------------------------
    // 2️⃣ Parser les options
    // ------------------------------------------------------------
    for(auto& opt : _options)
        opt->parse(argc, argv);

    // ------------------------------------------------------------
    //  Si --help est activé
    // ------------------------------------------------------------
    for(auto& opt : _options)
    {
        if(opt->enabled())
            return opt->execute();
    }

    // ------------------------------------------------------------
    // 3️⃣ Sinon on attend un symbole d'accord
    // ------------------------------------------------------------
    _chord = parse_chord(argv[1]);

    if(!_chord)
    {
        std::cerr << "Invalid chord symbol\n";
        return 1;
    }

    std::cout << *_chord << "\n";

    return 0;
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


// void ChordCommand::print_name() const
// {
//     std::cout << R"(
// ╔════════════════════════════════════════════════════════════╗
// ║                                                            ║
// ║    ██████╗██╗  ██╗ ██████╗ ██████╗ ██████╗                 ║
// ║   ██╔════╝██║  ██║██╔═══██╗██╔══██╗██╔══██╗                ║
// ║   ██║     ███████║██║   ██║██████╔╝██║  ██║                ║
// ║   ██║     ██╔══██║██║   ██║██╔══██╗██║  ██║                ║
// ║   ╚██████╗██║  ██║╚██████╔╝██║  ██║██████╔╝                ║
// ║    ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝                 ║
// ║                                                            ║
// ║              Guitar Harmony Exploration CLI                ║
// ║                      version 0.3.0                         ║
// ║                                                            ║
// ╚════════════════════════════════════════════════════════════╝
// )";
// }
void ChordCommand::print_name() const
{
    std::cout << R"(____ _                     _    ____ _     ___ 
  / ___| |__   ___  _ __ __ _| |  / ___| |   |_ _|
 | |   | '_ \ / _ \| '__/ _` | | | |   | |    | | 
 | |___| | | | (_) | | | (_| | | | |___| |___ | | 
  \____|_| |_|\___/|_|  \__,_|_|  \____|_____|___|

            Chord CLI — version 0.3.0

    )";
}
void ChordCommand::print_usage() const 
{
    std::cout << "Usage:\n";
    std::cout << "  chord [options] <symbol>\n";
    std::cout << "Try:\n";
    std::cout << "  chord --help\n";
}        

void ChordCommand::print_help() const
{
    print_name();
    std::cout << "\n";

    print_usage();
    std::cout << "\n";

    std::cout << "Options:\n";

    for (const auto& opt : _options)
        std::cout << *opt;
}
} // namespace cli::chord