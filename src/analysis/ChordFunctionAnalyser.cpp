#include <musical/analysis/ChordFunctionAnalyser.h>
#include <musical/analysis/ChordAnalysis.h>
//#include <musical/Core/note/NoteFactory.h>

#include <algorithm>

using namespace musical::analysis;

std::string ChordFunctionAnalyser::to_string(
	const musical::Chord& chord,
	const musical::ScaleKeyed& gamme)
{
    static const std::string romans_major[] = {"I", "II", "III", "IV", "V", "VI", "VII"};
    static const std::string romans_minor[] = {"i", "ii", "iii", "iv", "v", "vi", "vii"};    


     if (chord.size() == 0)
        return "?";

    const musical::core::Note root = chord.tonic();

    unsigned int root_val = root.chromatic_index();

    // Cherche la valeur de la fondamentale dans la gamme
    auto it = std::find_if(gamme.begin(), gamme.end(),
        [&](const musical::core::Note& n) { return n.chromatic_index() == root_val; });

    if (it == gamme.end())
        return "?";

    int degree = static_cast<int>(std::distance(gamme.begin(), it));

    if (degree < 0 || degree >= 7)
        return "?";

    if(musical::analysis::Chord::is_minor(chord))
        return romans_minor[degree];
    else
        return romans_major[degree];
}

