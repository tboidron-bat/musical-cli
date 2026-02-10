#include <musical/IO/chord/chord_formatter.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/note/NoteService.h>
#include <musical/Core/note/NoteFactory.h>
#include <musical/Analysis/chord_name.h>

#include <sstream>
#include <map>
#include <algorithm>

namespace musical::chord_formatter
{

// ============================================================
// Représentation textuelle linéaire
// ============================================================
std::string to_string(const Chord& chord)
{
    std::ostringstream oss;

    const auto& intervals = chord.intervals();

    // ─────────────────────────────
    // Tonique + intervalles (numériques)
    // ─────────────────────────────
    oss << chord.tonic();
    oss << '(';

    for (std::size_t idx = 0; idx < intervals.size(); ++idx)
    {
        oss << static_cast<int>(intervals[idx]);

        if (idx + 1 < intervals.size())
            oss << ", ";
    }

    oss << ") ";

    // ─────────────────────────────
    // Reconstruction des notes
    // ─────────────────────────────
    oss << "(";
    oss << chord.tonic();

    int root_pc  = NoteService::chromatic_index(chord.tonic());
    int root_oct = chord.tonic().GetPitch()._octave;

    for (IntervalType iv : intervals)
    {
        int semitones = static_cast<int>(iv);

        Note n = NoteFactory::create(root_pc + semitones, root_oct);
        oss << ", " << n;
    }

    oss << ") ";

    // ─────────────────────────────
    // Analyse harmonique
    // ─────────────────────────────
    const auto candidates = musical::analysis::chord_name::find(chord);

    if (!candidates.empty())
        oss << "= " << candidates.front().name;
    else
        oss << "= ?";

    return oss.str();
}


// ============================================================
// Traduction FR → EN
// ============================================================
std::string to_en(const std::string& name_fr)
{
    static const std::map<std::string, char> fr_to_en = {
        { "do",  'c' },
        { "ré",  'd' },
        { "mi",  'e' },
        { "fa",  'f' },
        { "sol", 'g' },
        { "la",  'a' },
        { "si",  'b' }
    };

    if (name_fr.empty())
        return name_fr;

    std::string name_en = name_fr;
    char first = static_cast<char>(std::tolower(static_cast<unsigned char>(name_fr[0])));

    if (first == 's' && name_fr.size() >= 2)
    {
        char second = static_cast<char>(std::tolower(static_cast<unsigned char>(name_fr[1])));
        if (second == 'o') return name_en.replace(0, 3, "g"); // sol
        if (second == 'i') return name_en.replace(0, 2, "b"); // si
    }
    else if (first == 'r')
    {
        return name_en.replace(0, 3, "d"); // ré
    }
    else if (name_fr.size() >= 2)
    {
        std::string root = name_fr.substr(0, 2);
        std::transform(root.begin(), root.end(), root.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        auto it = fr_to_en.find(root);
        if (it != fr_to_en.end())
            name_en.replace(0, 2, std::string(1, it->second));
    }

    return name_en;
}


// ============================================================
// Traduction EN → FR
// ============================================================
std::string to_fr(const std::string& name_en)
{
    static const std::map<char, std::string> en_to_fr = {
        { 'c', "Do" },
        { 'd', "Ré" },
        { 'e', "Mi" },
        { 'f', "Fa" },
        { 'g', "Sol" },
        { 'a', "La" },
        { 'b', "Si" }
    };

    if (name_en.empty())
        return name_en;

    std::string name_fr = name_en;
    char first = static_cast<char>(std::tolower(static_cast<unsigned char>(name_en[0])));

    auto it = en_to_fr.find(first);
    if (it != en_to_fr.end())
        name_fr.replace(0, 1, it->second);

    // Symboles jazz
    if (auto pos = name_fr.find("7M"); pos != std::string::npos)
        name_fr.replace(pos, 2, "△");

    if (auto pos = name_fr.find("M7"); pos != std::string::npos)
        name_fr.replace(pos, 2, "△");

    if (auto pos = name_fr.find("m7b5"); pos != std::string::npos)
        name_fr.replace(pos, 4, "ø");

    return name_fr;
}

} // namespace musical::chord_formatter
