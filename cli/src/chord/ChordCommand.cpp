#include <chord/ChordCommand.h>
#include <chord/Usage.h>
#include <command_option.h>

#include <chord/diagram_layout.h>

#include <musical/io/chord/input/ChordLexer.h>
#include <musical/io/chord/input/ChordParser.h>
#include <musical/io/chord/output/stream.h>
#include <musical/io/note/output/stream.h>
#include <musical/io/instruments/guitar/six_strings/stream.h>
#include <musical/io/instruments/guitar/six_strings/stream_diagram.h>
#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/instruments/guitar/six_strings/movable_shape_diagram_to_ascii.h>

#include <musical/audio/karplus_strong/chord_player.h>
#include <iostream>
#include <random>

//#define CHORD_COMMAND_DEBUG

#include <sys/ioctl.h>
#include <unistd.h>

static std::size_t terminal_width()
{
    struct winsize w{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
        return w.ws_col;

    return 120;
}

namespace cli::chord
{
ChordCommand::ChordCommand()
{
    add_option(
        static_cast<uint8_t>(OptionId::HELP),
        "help",
        "h",
        "Show help message");

    auto& diagram = add_option(
        static_cast<uint8_t>(OptionId::DIAGRAM),
        "diagram",
        "d",
        "Show chord diagram");

    diagram.add_argument({
        cli::command::option::argument_t::Type::INT,
        "position",
        "CAGED position (1–5)"
    });

    //std::vector<std::string>{ "1","2","3","4","5" }

    auto& random = add_option(
        static_cast<uint8_t>(OptionId::RANDOM),
        "random",
        "r",
        "Show a completely random chord");

    random.add_argument({
        cli::command::option::argument_t::Type::INT,
        "count",
        "number of chord to generate"
        });


    auto& play = add_option(
        static_cast<uint8_t>(OptionId::PLAY),
        "play",
        "",
        "Play the chord using Karplus-Strong guitar synthesis");

    play.add_argument({
        cli::command::option::argument_t::Type::INT,
        "delay",
        "<delay_ms>"
        });

    play.add_argument({
        cli::command::option::argument_t::Type::INT,
        "downstroke",
        "<downstroke>"
        });

        //  "Usage:\n"
        //  "  --play                 (simultaneous attack)\n"
        //  "  --play <delay_ms> <downstroke>\n"
        //  "\n"
        //  "Examples:\n"
        //  "  --play\n"
        //  "  --play 15\n"
        //  "  --play 20 false\n",

    auto& difficulty = add_option(        
        static_cast<uint8_t>(OptionId::DIFFICULTY),        
        "difficulty",
        "",
        "Filter diagrams by difficulty level (1–3)");
        //"Requires --diagram.",        

    difficulty.add_argument({
        cli::command::option::argument_t::Type::INT,
        "level",
        "1, 2, 3"
        });

    add_option( 
        static_cast<uint8_t>(OptionId::DUMP_DB),                      
        "dump-db",
        "",
        "Dump all chord diagrams stored in the database");

    auto& tuning = add_option(    
        static_cast<uint8_t>(OptionId::TUNING),            
        "tuning",
        "",
        "Guitar tuning to use for diagram rendering");
    //"Requires --diagram.",        

    tuning.add_argument({
        cli::command::option::argument_t::Type::STRING,
        "",
        "standard, dropd"
        });

        // "Supported tunings:\n"
        // "standard   (E A D G B E)\n"
        // "dropd      (D A D G B E)\n"
        // "Default: standard.\n"
}

// int ChordCommand::run(int argc, char** argv)
// {
//     for(auto& opt : _options)
//     {
//         if(opt.parse(argc, argv))
//             return opt.execute();
//     }

//     // comportement par défaut
// }

int ChordCommand::run(int argc, char** argv)
{
    // 1. parsing des options
    for(auto& opt : _options)
    {
        if(opt.parse(argc, argv))
            _options_bitmask |= static_cast<OptionId>(opt.id());
    }

    // 2. options sans symbole
    if(has_option(OptionId::HELP))
    {
        std::cout << get_help();
        return 0;
    }
    if(has_option(OptionId::DUMP_DB))
        return handle_option_dump_database();

    if(has_option(OptionId::RANDOM))
        return handle_option_random();

    // 3. symbole d'accord requis
    if(argc < 2)
    {
        std::cout << get_usage();
        return 1;
    }

    auto chord = parse_chord(argv[1]);

    if(!chord)
    {
        std::cerr << "Invalid chord symbol\n";
        return 1;
    }

    // 4. options avec symbole

    if(has_option(OptionId::DIAGRAM))
        return handle_option_show_diagrams(*chord);

    if(has_option(OptionId::PLAY))
    {
        handle_option_play(*chord);
        return 0;
    }

    // 5. comportement par défaut
    std::cout << *chord << "\n";
    return 0;
}// ============================================================
// Random mode
// ============================================================
int ChordCommand::handle_option_random() const
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    const bool choose_open = dist(gen) == 0;

    if (choose_open)
    {
        std::cout 
            << musical::instruments::guitar::six_strings::db_open_queries::get_random_diagram() 
            << "\n";
    }
    else
    {
        const auto diagram =
            musical::instruments::guitar::six_strings::db_movable_queries::get_random_diagram();

        std::cout
            << io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
            << "\n";
    }

    return 0;

}
// _____________________________________________________________
// Parse chord
// _____________________________________________________________
std::optional<musical::core::chord::Chord>
ChordCommand::parse_chord(const std::string& symbol) const
{
    using namespace musical::io::chord;

#ifdef CHORD_COMMAND_DEBUG
    std::cout << "ChordCommand::parse_chord(...) input=" << symbol << "\n";    
#endif

    auto tokens = ChordLexer::tokenize(symbol);

    auto chord_opt = ChordParser::parse(tokens);

    return chord_opt;
}


// _____________________________________________________________
// DUMP DATABASE
// _____________________________________________________________

int ChordCommand::handle_option_dump_database() const
{
    using namespace musical::instruments::guitar::six_strings;

    auto width = terminal_width();    

    std::cout
        << "[Open chord database]\n\n";

    std::vector<std::string> blocks;

    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<OpenChordDiagram::CAGEDShape>(s);

        const auto open_diagrams =
            db_open_queries::find_all_positions(shape);

	
        std::cout << ">> Shape " << shape << ": " << std::endl;
        //std::cout << std::string(width, '_') << std::endl;        

        for (const auto& diagram : open_diagrams)
        {
            std::ostringstream oss;
            oss << diagram;
            blocks.push_back(oss.str());
        }

        std::cout
            << cli::chord::layout_ascii_blocks(blocks, width);
        std::cout << std::string(width, '_') << std::endl;        
        std::cout << std::endl;

        blocks.clear();
    }


    std::cout
        << "\nMovable shape database\n\n";


    blocks.clear();
    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<OpenChordDiagram::CAGEDShape>(s);

        const auto movable_diagrams =
            db_movable_queries::find_all_positions(shape);

        for (const auto& diagram : movable_diagrams)
        {
            blocks.push_back(
                io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
            );
        }
    }
    std::cout
        << cli::chord::layout_ascii_blocks(blocks, width);


    return 0;
}
int ChordCommand::handle_option_show_diagrams(
    const musical::core::chord::Chord& chord)
{
    using musical::instruments::guitar::six_strings::OpenChordDiagram;

    int position = -1;

    if(auto* opt = find_option(OptionId::DIAGRAM))
    {
        if(opt->argument_count() >= 1 && !opt->value(0).empty())
        {
            try
            {
                position = std::stoi(opt->value(0));
            }
            catch(...)
            {
                std::cerr << "Invalid diagram position\n";
                return 1;
            }
        }
    }    

    auto width = terminal_width();    

    bool found = false;

    std::vector<std::string> blocks;    

    for (int s = 0; s < 5; ++s)
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

void ChordCommand::handle_option_play(
    const musical::core::chord::Chord& chord)
{
    double strum_delay_ms = 0.0;
    bool downstroke = true;

    if(auto* opt = find_option(OptionId::PLAY))
    {
        try
        {
            if(opt->argument_count() >= 1 && !opt->value(0).empty())
                strum_delay_ms = std::stod(opt->value(0));

            if(opt->argument_count() >= 2 && !opt->value(1).empty())
                downstroke = (opt->value(1) == "true");
        }
        catch(...)
        {
            std::cerr << "Invalid arguments for --play\n";
            return;
        }
    }

    std::cout << "Playing chord: " << chord << "\n";

    musical::audio::karplus_strong::ChordPlayer::play(
        chord,
        strum_delay_ms,
        downstroke
    );
}

std::string ChordCommand::get_name() const {

    return "chord";
}

std::string ChordCommand::get_description() const
{
    return "Chord exploration tool for guitar diagrams and synthesis.";
}

std::string ChordCommand::get_usage() const
{
    std::ostringstream oss;

    oss << "Usage:\n";
    oss << "  chord [options] <symbol>\n\n";
    oss << "Try:\n";
    oss << "  chord --help\n";

    return oss.str();
}

std::string ChordCommand::get_help() const
{
    std::ostringstream oss;

    oss << "Command: " << get_name() << "\n";
    oss << get_description() << "\n\n";

    oss << get_usage() << "\n";

    oss << "Options:\n";

    for(const auto& opt : _options)
    {
        oss << "  " << opt << "\n";
    }

    return oss.str();
}
} // namespace cli::chord