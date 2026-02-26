#include <chord/ChordCommand.h>
#include <chord/Usage.h>
#include <ArgumentParser.h>

#include <musical/io/chord/input/ChordLexer.h>
#include <musical/io/chord/input/ChordParser.h>
#include <musical/io/chord/input/tokens.h>

#include <musical/io/chord/output/stream.h>
#include <musical/io/note/output/stream.h>

#include <musical/instruments/guitar/six_strings/database_queries.h>
#include <musical/io/instruments/guitar/six_strings/chord_diagram/to_ascii.h>

#include <musical/audio/karplus_strong/chord_player.h>

#include <iostream>

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
    auto diagram =
        guitar::six_strings::chord_diagram::database_queries::get_random_diagram();

    std::cout << "Random chord:\n";
    std::cout
        << io::instruments::guitar::six_strings::chord_diagram::to_ascii(diagram)
        << "\n";

    return 0;
}


// ============================================================
// Symbol mode
// ============================================================

int ChordCommand::handle_symbol(
    const std::string& symbol,
    const cli::globalconfig_t& global) const
{
    std::cout << "symbol=" << symbol << "\n";

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
    bool show_diagram =
        global.options.count("--diagram") ||
        global.options.count("-d");

    if (show_diagram)
        return show_diagrams(chord);

    return 0;
}


// ============================================================
// Parse chord
// ============================================================

std::optional<musical::core::chord::Chord>
ChordCommand::parse_chord(const std::string& symbol) const
{
    using namespace musical::io::chord;

    auto tokens = ChordLexer::tokenize(symbol);

    if (tokens.empty())
    {
        std::cerr << "Chord lexing failed\n";
        return std::nullopt;
    }

    std::cout << "Tokens:\n";

    for (const auto& t : tokens)
    {
        switch (t.type)
        {
            case TokenType::ROOT:
                std::cout << "  ROOT: "
                          << std::get<RootToken>(t.value).text
                          << "\n";
                break;

            case TokenType::LEXEME:
            {
                const auto& lex =
                    std::get<LexemeToken>(t.value);

                std::cout << "  LEXEME: "
                          << lex.text
                          << " (" << lex.category << ")\n";
                break;
            }

            case TokenType::SLASH:
                std::cout << "  SLASH\n";
                break;

            case TokenType::UNKNOWN:
                std::cout << "  UNKNOWN\n";
                break;
        }
    }

    auto chord_opt = ChordParser::parse(tokens);

    if (!chord_opt)
    {
        std::cerr << "Chord parsing failed\n";
        return std::nullopt;
    }

    return chord_opt;
}


// ============================================================
// Diagram display
// ============================================================

int ChordCommand::show_diagrams(
    const musical::core::chord::Chord& chord) const
{
    using musical::instruments::guitar::six_strings::ChordDiagram;

    bool found = false;

    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<ChordDiagram::CAGEDShape>(s);

        const auto diagrams =
            guitar::six_strings::chord_diagram::database_queries::find_positions(
                chord.root(),
                chord.type(),
                shape,
                guitar::six_strings::chord_diagram::database_queries::PositionKind::OPEN
            );

        for (const auto& diagram : diagrams)
        {
            std::cout
                << io::instruments::guitar::six_strings::chord_diagram::to_ascii(diagram)
                << "\n";

            found = true;
        }
    }

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