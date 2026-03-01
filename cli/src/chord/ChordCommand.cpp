#include <chord/ChordCommand.h>
#include <chord/Usage.h>
#include <ArgumentParser.h>
#include <chord/diagram_layout.h>

#include <musical/io/chord/input/ChordLexer.h>
#include <musical/io/chord/input/ChordParser.h>
#include <musical/io/chord/output/stream.h>
#include <musical/io/note/output/stream.h>
#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/instruments/guitar/six_strings/open_chord_diagram_to_ascii.h>
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
const std::vector<cli::option_t>&
ChordCommand::options() const
{
    static const std::vector<cli::option_t> opts =
    {
        {
            "--diagram",
            "-d",
            "Show chord diagram.\n"
            "If <value> (1–5) is provided, show only that CAGED position.",
            true,
            true,
            1,
            std::vector<std::string>{ "1","2","3","4","5" }
        },
        {
            "--random",
            "-r",
            "Show a completely random chord.",
            false,
            false,
            0,
            {}
        },
        {
            "--play",
            "",
            "Play the chord using Karplus-Strong guitar synthesis.\n"
            "Usage:\n"
            "  --play                 (simultaneous attack)\n"
            "  --play <delay_ms>\n"
            "  --play <delay_ms> <downstroke>\n"
            "\n"
            "Examples:\n"
            "  --play\n"
            "  --play 15\n"
            "  --play 20 false\n",
            true,   // accepte des valeurs (0 à 2)
            true,   // valeurs optionnelles
            2,
            {}
        },
        {
            "--difficulty",
            "",
            "Filter diagrams by difficulty level (1–3).\n"
            "Requires --diagram.",
            true,
            false,
            1,
            std::vector<std::string>{ "1","2","3" }
        },
        {
            "--dump-db",
            "",
            "Dump all chord diagrams stored in the database.",
            false,
            false,
            0,
            {}
        },        
        {
            "--tuning",
            "",
            "Guitar tuning to use for diagram rendering.\n"
            "Supported tunings:\n"
            "standard   (E A D G B E)\n"
            "dropd      (D A D G B E)\n"
            "Default: standard.\n"
            "Requires --diagram.",
            true,
            false,
            1,
            std::vector<std::string>{ "standard","dropd" }
        }
    };

    return opts;
}    

// ============================================================
// Entry point
// ============================================================

int ChordCommand::run(int argc, char** argv)
{
    cli::globalconfig_t global =
        cli::ArgumentParser::parse(argc, argv);

    if (global.help)
    {
        print_help(*this);
        return 0;
    }

    if (global.version)
    {
        std::cout << "chord 0.01\n";
        return 0;
    }

    if (global.options.count("--dump-db"))
    {
        return dump_database();
    }    

    if (global.options.count("--random") ||
        global.options.count("-r"))
    {
        return handle_random();
    }

    if (global.positional_args.empty())
    {
        print_usage();
        return 1;
    }

    return handle_symbol(global.positional_args.front(), global);
}


// ============================================================
// Random mode
// ============================================================
int ChordCommand::handle_random() const
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    const bool choose_open = dist(gen) == 0;

    if (choose_open)
    {
        const auto diagram =
            musical::instruments::guitar::six_strings::db_open_queries::get_random_diagram();

        std::cout
            << io::guitar::six_strings::open_chord_diagram_to_ascii(diagram)
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

// ============================================================
// Symbol mode
// ============================================================

int ChordCommand::handle_symbol(
    const std::string& symbol,
    const cli::globalconfig_t& global) const
{
    auto chord_opt = parse_chord(symbol);

    if (!chord_opt)
        return 1;

    const auto& chord = *chord_opt;

    std::cout << chord << "\n";

    // ---- PLAY
    auto it = global.options.find("--play");

    if (it != global.options.end())
    {
        double strum_delay = 0.0;
        bool downstroke = true;

        const auto& values = it->second;

        if (values.size() >= 1)
        {
            try
            {
                strum_delay = std::stod(values[0]);
            }
            catch (...)
            {
                std::cerr << "--play expects a numeric delay\n";
                return 1;
            }
        }
        if (values.size() >= 2)
            downstroke = (values[1] == "true");

        play_chord(chord, strum_delay, downstroke);
    }


    auto it_d = global.options.find("--diagram");
    if (it_d == global.options.end())
        it_d = global.options.find("-d");

    if (it_d != global.options.end())
    {
        const auto& values = it_d->second;

        if (values.empty())
        {
            return show_diagrams(chord, -1); // toutes positions
        }

        try
        {
            int position = std::stoi(values[0]);
            return show_diagrams(chord, position);
        }
        catch (...)
        {
            std::cerr << "Invalid diagram position\n";
            return 1;
        }
    }    
    return 0;
}


// ============================================================
// Parse chord
// ============================================================

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


// ============================================================
// DUMP DATABASE
// ============================================================

int ChordCommand::dump_database() const
{
    using namespace musical::instruments::guitar::six_strings;

    auto width = terminal_width();    

    std::cout
        << "\nOpen chord database\n\n";

    std::vector<std::string> blocks;

    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<OpenChordDiagram::CAGEDShape>(s);

        const auto open_diagrams =
            db_open_queries::find_all_positions(shape);

        for (const auto& diagram : open_diagrams)
        {
            blocks.push_back(
                io::guitar::six_strings::open_chord_diagram_to_ascii(diagram)
            );
        }
    }
    std::cout
        << cli::chord::layout_ascii_blocks(blocks, width);


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
int ChordCommand::show_diagrams
    (
    const musical::core::chord::Chord& chord,
    int position) const
{
    using musical::instruments::guitar::six_strings::OpenChordDiagram;

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
            blocks.push_back(
                io::guitar::six_strings::open_chord_diagram_to_ascii(diagram)
            );
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

void ChordCommand::play_chord(
    const musical::core::chord::Chord& chord,
    double strum_delay_ms,
    bool downstroke) const
{
    std::cout << "Playing chord: " << chord << "\n";

    musical::audio::karplus_strong::ChordPlayer::play(chord,strum_delay_ms,downstroke);

}

} // namespace cli::chord