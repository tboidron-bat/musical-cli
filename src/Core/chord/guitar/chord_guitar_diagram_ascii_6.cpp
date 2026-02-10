#include <musical/Core/chord/guitar/chord_guitar_diagram_ascii_6.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/guitar/chord_guitar_diagram.h>
#include <musical/Core/chord/guitar/chord_guitar_diagram_db_6.h>
#include <musical/IO/chord/chord_formatter.h>


#include <array>
#include <sstream>
#include <iostream>

namespace musical::chord::guitar::diagram_ascii_6 {

// ------------------------------------------------------------------
// Configuration FIXE : guitare 6 cordes
// ------------------------------------------------------------------

static constexpr uint8_t NB_STRINGS = 6;
static constexpr uint8_t NB_FRETS   = 4;

static constexpr std::array<char, NB_STRINGS> STRING_NAME_EN =
{
    'E','A','D','G','B','E'
};

// ------------------------------------------------------------------
// Utilitaire : chiffre romain (pour base_fret)
// ------------------------------------------------------------------

static std::string to_roman(uint8_t value)
{
    static const std::pair<uint8_t, const char*> romans[] = {
        {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}
    };

    std::string result;
    for (auto& [v, s] : romans)
    {
        while (value >= v)
        {
            result += s;
            value -= v;
        }
    }
    return result;
}

// ------------------------------------------------------------------
// Dessin de la grille vide
// ------------------------------------------------------------------

static std::string draw_ascii_grid(uint8_t base_fret)
{
    std::ostringstream oss;

    // En-tête : noms des cordes
    for (char s : STRING_NAME_EN)
        oss << s << ' ';
    oss << '\n';

    oss << std::string(NB_STRINGS * 2 + 1, '-') << '\n';

    for (uint8_t f = 0; f < NB_FRETS; ++f)
    {
        for (uint8_t c = 0; c < NB_STRINGS; ++c)
            oss << "| ";

        if (f == 0 && base_fret > 0)
            oss << " " << to_roman(base_fret);

        oss << '\n';
    }

    return oss.str();
}

// ------------------------------------------------------------------
// Rendu ASCII depuis un Diagram<6>
// ------------------------------------------------------------------

std::string to_ascii(const Diagram<6>& diagram)
{
    using D  = Diagram<6>;
    using SS = D::string_state;

    std::ostringstream oss;
    oss << draw_ascii_grid(diagram._base_fret);

    // Repositionnement curseur au début de la grille
    oss.seekp(0, std::ios_base::beg);
    std::size_t cursor = 0;

    // Sauter l’en-tête (noms des cordes)
    cursor += NB_STRINGS * 2 + 1;
    oss.seekp(cursor, std::ios_base::beg);

    // Cordes à vide / étouffées
    for (const auto& sp : diagram._strings)
    {
        if (sp.fret == 0)
            oss.put('0');
        else if (sp.fret == SS::MUTED)
            oss.put('x');
        else
            oss.put('|');   // ← IMPORTANT : placeholder explicite

        cursor += 2;
        oss.seekp(cursor, std::ios_base::beg);

    }

    cursor += 1;
    oss.seekp(cursor, std::ios_base::beg);

    // Doigtés
    for (uint8_t f = 1; f <= NB_FRETS; ++f)
    {
        for (const auto& sp : diagram._strings)
        {
            if (sp.fret == f && sp.finger > 0)
                oss.put(static_cast<char>('0' + sp.finger));

            cursor += 2;
            oss.seekp(cursor, std::ios_base::beg);
        }
        cursor += 1;
        oss.seekp(cursor, std::ios_base::beg);
    }

    return oss.str();
}

// ------------------------------------------------------------------
// API publique : accord -> diagramme ASCII guitare
// ------------------------------------------------------------------

std::string to_ascii(const musical::Chord& chord)
{
    using Diagram6 = Diagram<6>;

    const auto& db = database<6>();
    const auto& tuning_db = db.at(GuitarTuning::STANDARD);

    auto it = tuning_db.find(chord.intervals());
    if (it == tuning_db.end() || it->second.empty())
    {
        return "[no guitar diagram for chord: "
             + musical::chord_formatter::to_string(chord) + "]";
    }

    const Diagram6& diagram = it->second.front();
    return to_ascii(diagram);
}

} // namespace musical::chord::guitar::diagram_ascii_6
