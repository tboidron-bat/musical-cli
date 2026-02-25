#include <musical/io/instruments/guitar/six_strings/chord_diagram/to_ascii.h>

#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/ChordType.h>
#include <musical/instruments/guitar/six_strings/ChordDiagram.h>

#include <musical/io/chord/formatter.h>

#include <array>
#include <sstream>
#include <iostream>

namespace io::instruments::guitar::six_strings::chord_diagram {

    namespace sst = musical::instruments::guitar::six_strings;

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

static std::string draw_ascii_grid(uint8_t base_fret, uint8_t nb_frets)
{
    std::ostringstream oss;

    // En-tête : noms des cordes
    for (char s : {'E', 'A', 'D', 'G', 'B', 'E'})
        oss << s << ' ';
    oss << '\n';

    namespace sst = musical::instruments::guitar::six_strings;
    oss << std::string(sst::ChordDiagram::STRING_COUNT * 2 + 1, '-') << '\n';

    for (uint8_t f = 0; f < nb_frets; ++f)
    {
        for (uint8_t c = 0; c < sst::ChordDiagram::STRING_COUNT; ++c)
            oss << "| ";

        if (f == 0 && base_fret > 0)
            oss << " " << to_roman(base_fret);

        oss << '\n';
    }

    return oss.str();
}

// ------------------------------------------------------------------
// Rendu ASCII depuis un ChordDiagram
// ------------------------------------------------------------------

std::string to_ascii(const sst::ChordDiagram& diagram)
{
    using D  = sst::ChordDiagram;
    using SS = sst::ChordDiagram::string_state;

    const auto& strings = diagram.strings();

    uint8_t first = diagram.first_fret();
    uint8_t height = diagram.nb_frets();

    if (height == 0)
        height = 1;

    std::ostringstream oss;

    // En-tête
    // for (char s : {'E','A','D','G','B','E'})
    //     oss << s << ' ';
    // oss << '\n';

    // Ligne open / muted
    for (const auto& sp : strings)
    {
        if (sp.state() == SS::State::OPEN_STRING)
            oss << "0 ";
        else if (sp.state() == SS::State::MUTED)
            oss << "x ";
        else
            oss << "  ";
    }
    oss << '\n';

    oss << std::string(D::STRING_COUNT * 2 - 1, '=') << '\n';    

    // Corps : une ligne par frette réelle
    for (uint8_t row = 0; row < height; ++row)
    {
        uint8_t current_fret = first + row;

        for (const auto& sp : strings)
        {
            if (sp.state() == SS::State::FRETTED &&
                sp.fret() == current_fret)
            {
                oss << static_cast<char>('0' + sp.finger()) << ' ';
            }
            else
            {
                oss << "| ";
            }
        }

        if (row == 0 && diagram.needs_fret_label())
            oss << "  " << current_fret;

        oss << '\n';
    }

    return oss.str();
}
} // namespace io::instruments::guitar::chord_diagram