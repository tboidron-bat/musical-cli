#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/ChordFactory.h>
#include <musical/io/chord/chord_formatter.h>
#include <musical/instruments/guitar/chord_guitar_diagram_ascii_6.h>
#include <musical/instruments/guitar/chord_guitar_diagram_db_6.h>
#include <musical/Core/note/Factory.h>

#include <musical/analysis/chord_name.h>

#include <iostream>
#include <string>

enum class OutputFormat
{
    Text,
    Guitar,
    All,
    AllDiagrams
};

static std::string chord_name_or_fallback(const musical::Chord& chord)
{
    using musical::analysis::chord_name::find;

    auto candidates = find(chord);
    if (!candidates.empty())
        return candidates.front().name;

    return musical::chord_formatter::to_string(chord);
}
static std::string strip_tonic(const std::string& name)
{
    if (name.empty())
        return name;

    // Supprimer la lettre de note (A–G)
    size_t pos = 1;

    // Gérer altérations (#, b)
    if (pos < name.size() && (name[pos] == '#' || name[pos] == 'b'))
        ++pos;

    return name.substr(pos);
}



int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr <<
            "usage:\n"
            "  chord <symbol> [--format=text|guitar|all]\n"
            "  chord --all    (list all guitar diagrams)\n";
        return 1;
    }

    OutputFormat format = OutputFormat::All;
    std::string symbol;

    // --- parsing des arguments ---
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--all")
        {
            format = OutputFormat::AllDiagrams;
        }
        else if (arg == "--format=text")
        {
            format = OutputFormat::Text;
        }
        else if (arg == "--format=guitar")
        {
            format = OutputFormat::Guitar;
        }
        else if (arg == "--format=all")
        {
            format = OutputFormat::All;
        }
        else if (arg.substr(0, 2) != "--")
        {
            symbol = arg;
        }
        else
        {
            std::cerr << "unknown option: " << arg << "\n";
            return 1;
        }
    }

    // ============================================================
    // --all : afficher toute la base de diagrammes guitare 6 cordes
    // ============================================================
    if (format == OutputFormat::AllDiagrams)
    {
        using musical::chord::guitar::database;
        using musical::chord::guitar::diagram_ascii_6::to_ascii;

        const auto& db = database<6>();

        std::cout << "=== Guitar diagrams database (6 strings) ===\n\n";

        for (const auto& [tuning, tuning_db] : db)
        {
            std::cout << "Tuning: " << static_cast<int>(tuning) << "\n\n";

            for (const auto& [intervals, diagrams] : tuning_db)
            {
                // Tonique fictive pour analyse harmonique (C4)
                musical::core::Note tonic = musical::NoteFactory::create(0);

                musical::Chord abstract_chord(tonic, intervals);

                std::string full_name = chord_name_or_fallback(abstract_chord);

                std::cout
                    << "Chord: "
                    << strip_tonic(full_name)
                    << "\n";



                for (size_t i = 0; i < diagrams.size(); ++i)
                {
                    std::cout << "Diagram " << (i + 1) << ":\n";
                    std::cout << 
                    musical::chord::guitar::diagram_ascii_6::to_ascii(diagrams[i]) << "\n";
                }

                std::cout << "\n";
            }
        }

        return 0;
    }

    // ============================================================
    // Commande normale : accord unique
    // ============================================================
    if (symbol.empty())
    {
        std::cerr << "error: no chord symbol provided\n";
        return 1;
    }

    try
    {
        musical::Chord chord = musical::ChordFactory::create(symbol);

        if (chord.size() == 0)
        {
            std::cerr << "error: empty chord\n";
            return 1;
        }

        switch (format)
        {
            case OutputFormat::Text:
                std::cout
                    << musical::chord_formatter::to_string(chord)
                    << "\n";
                break;

            case OutputFormat::Guitar:
                std::cout
                    << musical::chord::guitar::diagram_ascii_6::to_ascii(chord)
                    << "\n";
                break;

            case OutputFormat::All:
                std::cout
                    << musical::chord_formatter::to_string(chord)
                    << "\n";
                std::cout
                    << musical::chord::guitar::diagram_ascii_6::to_ascii(chord)
                    << "\n";
                break;

            default:
                break;
        }
    }
    catch (...)
    {
        std::cerr << "error: invalid chord '" << symbol << "'\n";
        return 2;
    }

    return 0;
}
