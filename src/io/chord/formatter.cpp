#include <musical/io/chord/formatter.h>
#include <musical/io/note/stream.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/pitch_t.h>
#include <musical/analysis/chord_name.h>

#include <sstream>
#include <map>
#include <algorithm>

namespace musical::io::chord::formatter
{

std::string to_string(const core::chord::Chord& chord)
{
    std::ostringstream oss;

    const auto& intervals = chord.type().intervals();

    // ─────────────────────────────
    // Tonique + intervalles numériques
    // ─────────────────────────────
    oss << chord.root();

    oss << '(';

    for (std::size_t i = 0; i < intervals.size(); ++i)
    {
        oss << static_cast<int>(intervals[i]);

        if (i + 1 < intervals.size())
            oss << ", ";
    }

    oss << ") ";

    // ─────────────────────────────
    // Reconstruction harmonique
    // ─────────────────────────────
    oss << "(";
    oss << chord.root();

    int root_pc = static_cast<int>(
        musical::core::chromatic_index(chord.root())
    );

    for (core::IntervalType iv : intervals)
    {
        int semitones = static_cast<int>(iv);
        int new_index = (root_pc + semitones) % 12;

        // ⚠️ nécessite pitch_from_chromatic_index
        auto p = musical::core::pitch_from_chromatic_index(new_index, true);

        oss << ", " << p;
    }

    oss << ") ";

    // ─────────────────────────────
    // Analyse harmonique
    // ─────────────────────────────
    const auto candidates =
        musical::analysis::chord_name::find(chord);

    if (!candidates.empty())
        oss << "= " << candidates.front().name;
    else
        oss << "= ?";

    return oss.str();
}
}