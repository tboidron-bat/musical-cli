#include <chord/ChordCommand.h>
#include <chord/Usage.h>
#include <ArgumentParser.h>

#include <musical/io/chord/input/Lexer.h>
#include <musical/io/chord/input/Parser.h>
#include <musical/io/chord/input/tokens.h>

#include <musical/io/chord/output/stream.h>

#include <musical/instruments/guitar/six_strings/database_by_shape.h>
#include <musical/io/instruments/guitar/six_strings/chord_diagram/to_ascii.h>

#include <iostream>
#include <optional>

// ------------------------------------------------------------
// Debug helper
// ------------------------------------------------------------
static const char* to_string(musical::io::chord::LexemeCategory cat)
{
    using C = musical::io::chord::LexemeCategory;

    switch (cat)
    {
        case C::TRIAD:       return "TRIAD";
        case C::SEVENTH:     return "SEVENTH";
        case C::EXTENSION:   return "EXTENSION";
        case C::ALTERATION:  return "ALTERATION";
        case C::SUSPENSION:  return "SUSPENSION";
        case C::ADDITION:    return "ADDITION";
        case C::SPECIAL:     return "SPECIAL";
    }

    return "UNKNOWN";
}

namespace cli::chord
{

// ------------------------------------------------------------
// Options
// ------------------------------------------------------------
const std::vector<cli::option_t>& 
ChordCommand::options() const 
{
    static const std::vector<cli::option_t> opts =
    {
        { "--diagram",    "-d", "Show chord diagram [CAGED position 1–5 optional]" },
        { "--difficulty", "",   "Filter diagrams by difficulty level (1–3)" },
        { "--tuning",     "",   "Guitar tuning (standard, dropd, dadgad, openG, openD)" },                        
        { "--help",       "-h", "Show this help message" }
    };

    return opts;
}

// ------------------------------------------------------------
// Run
// ------------------------------------------------------------
int ChordCommand::run(int argc, char** argv)
{
    auto global = cli::ArgumentParser::parse(argc, argv);

    // --------------------------------------------------------
    // Global flags
    // --------------------------------------------------------
    if (global.help)
    {
        print_help();
        return 0;
    }

    if (global.version)
    {
        std::cout << "chord 0.01\n";
        return 0;
    }

    if (global.positional_args.empty())
    {
        print_usage();
        return 1;
    }

    // --------------------------------------------------------
    // CLI options
    // --------------------------------------------------------
    bool show_diagram = false;
    std::optional<int> position;
    std::optional<int> difficulty;

    // ---- Diagram (long or short)
    auto it_long  = global.options.find("--diagram");
    auto it_short = global.options.find("-d");

    auto it = (it_long != global.options.end())
              ? it_long
              : it_short;

    if (it != global.options.end())
    {
        show_diagram = true;

        if (it->second) // valeur fournie
        {
            try
            {
                int p = std::stoi(*(it->second));

                if (p < 1 || p > 5)
                {
                    std::cerr << "Error: position must be between 1 and 5\n";
                    return 1;
                }

                position = p;
            }
            catch (...)
            {
                std::cerr << "Error: invalid diagram position\n";
                return 1;
            }
        }
    }

    // ---- Difficulty
    auto itd = global.options.find("--difficulty");

    if (itd != global.options.end())
    {
        if (!show_diagram)
        {
            std::cerr << "Error: --difficulty requires --diagram\n";
            return 1;
        }

        if (!itd->second)
        {
            std::cerr << "Error: --difficulty requires a value (1–3)\n";
            return 1;
        }

        try
        {
            int d = std::stoi(*(itd->second));

            if (d < 1 || d > 3)
            {
                std::cerr << "Error: difficulty must be between 1 and 3\n";
                return 1;
            }

            difficulty = d;
        }
        catch (...)
        {
            std::cerr << "Error: invalid difficulty value\n";
            return 1;
        }
    }

    // --------------------------------------------------------
    // 1️⃣ Symbol
    // --------------------------------------------------------
    const std::string symbol = global.positional_args.front();

    std::cout << "symbol=" << symbol << "\n";

    // --------------------------------------------------------
    // 2️⃣ Lexer
    // --------------------------------------------------------
    auto tokens =
        musical::io::chord::Lexer::tokenize(symbol);

    if (tokens.empty())
    {
        std::cerr << "Chord lexing failed\n";
        return 1;
    }

    std::cout << "Tokens:\n";

    for (const auto& t : tokens)
    {
        switch (t.type)
        {
            case musical::io::chord::TokenType::ROOT:
                std::cout << "  ROOT: "
                          << std::get<musical::io::chord::RootToken>(t.value).text
                          << "\n";
                break;

            case musical::io::chord::TokenType::LEXEME:
            {
                const auto& lex =
                    std::get<musical::io::chord::LexemeToken>(t.value);

                std::cout << "  LEXEME: "
                          << lex.text
                          << " ("
                          << to_string(lex.category)
                          << ")\n";
                break;
            }

            case musical::io::chord::TokenType::SLASH:
                std::cout << "  SLASH\n";
                break;

            case musical::io::chord::TokenType::UNKNOWN:
                std::cout << "  UNKNOWN: "
                          << std::get<musical::io::chord::RootToken>(t.value).text
                          << "\n";
                break;
        }
    }

    // --------------------------------------------------------
    // 3️⃣ Parser
    // --------------------------------------------------------
    auto chord_opt =
        musical::io::chord::Parser::parse(tokens);     

    if (!chord_opt)
    {
        std::cerr << "Chord parsing failed\n";
        return 1;
    }

    const auto& chord = *chord_opt;

    std::cout << chord << std::endl;

    //auto v_intervals = chord.type().intervals();

    //std::sort(v_intervals.begin(), v_intervals.end());    

    // --------------------------------------------------------
    // 4️⃣ Output mode
    // --------------------------------------------------------
    if (show_diagram)
    {

        using namespace musical::instruments::guitar::six_strings;

        bool found = false;

        for (int s = 0; s < 5; ++s)
        {
            auto shape = static_cast<ChordDiagram::CAGEDShape>(s);

            const auto& db = database_for_shape(shape);

            auto chord_it = db.find(chord.type());

            if (chord_it == db.end())
                continue;

            const auto& diagrams = chord_it->second;

            for (const auto& diagram : diagrams)
            {
                std::cout <<
                    io::instruments::guitar::six_strings::chord_diagram::to_ascii(diagram)
                    << "\n";

                found = true;
            }
        }

        if (!found)
        {
            std::cerr << "No diagram found for this chord formula\n";
            return 1;
        }
        std::cout << "Find Diagram in DB" << std::endl;     
    }

    return 0;
}

} // namespace cli::chord