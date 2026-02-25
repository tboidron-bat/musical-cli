#include <musical/analysis/ChordFunctionAnalyser.h>
#include <musical/analysis/ChordAnalysis.h>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/scale/ScaleKeyed.h>

#include <musical/Core/pitch_t.h>

#include <algorithm>

namespace musical::analysis
{

std::string ChordFunctionAnalyser::to_string(
    const musical::core::chord::Chord& chord,
    const musical::core::scale::ScaleKeyed& gamme)
{
    using musical::core::pitch_t;
    using musical::core::chromatic_index;

    static const std::string romans_major[] =
        {"I","II","III","IV","V","VI","VII"};

    static const std::string romans_minor[] =
        {"i","ii","iii","iv","v","vi","vii"};

    if (chord.size() == 0)
        return "?";

    pitch_t root = chord.root();
    int root_val = static_cast<int>(chromatic_index(root));

    auto it = std::find_if(
        gamme.begin(),
        gamme.end(),
        [&](const pitch_t& p)
        {
            return chromatic_index(p) == root_val;
        });

    if (it == gamme.end())
        return "?";

    int degree = static_cast<int>(
        std::distance(gamme.begin(), it)
    );

    if (degree < 0 || degree >= 7)
        return "?";

    if (analysis::chord::is_minor(chord))
        return romans_minor[degree];
    else
        return romans_major[degree];
}

} // namespace musical::analysis