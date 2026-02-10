#include <musical/Analysis/ChordFunctionAnalyser.h>
#include <musical/Analysis/ChordAnalysis.h>
#include <musical/Core/note/NoteService.h>

#include <algorithm>

using namespace musical::Analysis;

std::string ChordFunctionAnalyser::to_string(
	const musical::Chord& chord,
	const musical::ScaleKeyed& gamme)
{
    static const std::string romans_major[] = {"I", "II", "III", "IV", "V", "VI", "VII"};
    static const std::string romans_minor[] = {"i", "ii", "iii", "iv", "v", "vi", "vii"};    


     if (chord.size() == 0)
        return "?";

    const musical::Note root = chord.tonic();

    unsigned int root_val = NoteService::chromatic_index(root);

    // Cherche la valeur de la fondamentale dans la gamme
    auto it = std::find_if(gamme.begin(), gamme.end(),
        [&](const musical::Note& n) { return NoteService::chromatic_index(n) == root_val; });

    if (it == gamme.end())
        return "?";

    int degree = static_cast<int>(std::distance(gamme.begin(), it));

    if (degree < 0 || degree >= 7)
        return "?";

    if(musical::Analysis::Chord::is_minor(chord))
        return romans_minor[degree];
    else
        return romans_major[degree];
}

