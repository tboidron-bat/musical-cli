#include <musical/io/instruments/guitar/six_strings/open_chord_diagram_to_ascii.h>


#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/ChordType.h>
#include <musical/instruments/guitar/six_strings/OpenChordDiagram.h>

#include <array>
#include <sstream>
#include <iostream>

namespace io::guitar::six_strings {

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

// static std::string draw_ascii_grid(uint8_t base_fret, uint8_t nb_frets)
// {
//     std::ostringstream oss;

//     // En-tête : noms des cordes
//     for (char s : {'E', 'A', 'D', 'G', 'B', 'E'})
//         oss << s << ' ';
//     oss << '\n';

//     namespace sst = musical::instruments::guitar::six_strings;
//     oss << std::string(sst::OpenChordDiagram::STRING_COUNT * 2 + 1, '-') << '\n';

//     for (uint8_t f = 0; f < nb_frets; ++f)
//     {
//         for (uint8_t c = 0; c < sst::OpenChordDiagram::STRING_COUNT; ++c)
//             oss << "| ";

//         if (f == 0 && base_fret > 0)
//             oss << " " << to_roman(base_fret);

//         oss << '\n';
//     }

//     return oss.str();
// }

// ------------------------------------------------------------------
// Rendu ASCII depuis un OpenChordDiagram
// ------------------------------------------------------------------
// static std::string shape_to_string(sst::OpenChordDiagram::CAGEDShape shape)
// {
//     switch (shape)
//     {
//         case sst::OpenChordDiagram::CAGEDShape::C: return "C";
//         case sst::OpenChordDiagram::CAGEDShape::A: return "A";
//         case sst::OpenChordDiagram::CAGEDShape::G: return "G";
//         case sst::OpenChordDiagram::CAGEDShape::E: return "E";
//         case sst::OpenChordDiagram::CAGEDShape::D: return "D";
//     }
//     return "?";
// }
std::string open_chord_diagram_to_ascii(const sst::OpenChordDiagram& diagram)
{
    using D  = sst::OpenChordDiagram;
    using SS = sst::OpenChordDiagram::string_state;

    const auto& strings = diagram.strings();

    uint8_t first_real = diagram.first_fret();
    uint8_t height = diagram.nb_frets();

    if (height == 0)
        height = 1;

    // 🔥 logique d’affichage
    uint8_t start =
        (first_real <= 4) ? 1 : first_real;

    // si on affiche depuis 1, on doit ajuster la hauteur
    if (start == 1)
    {
        uint8_t last_real = first_real + diagram.nb_frets() - 1;
        height = std::max<uint8_t>(4, last_real);
    }
        
    std::ostringstream oss;

    // // 🔥 Affichage de la shape
    // oss << "[Shape "
    //     << shape_to_string(diagram.shape())
    //     << "]\n";    

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

    if (!diagram.needs_fret_label())
        oss << std::string(D::STRING_COUNT * 2 - 1, '=') << '\n';
    else
        oss << std::string(D::STRING_COUNT * 2 - 1, '-') << '\n';

    // Corps : une ligne par frette réelle
    for (uint8_t row = 0; row < height; ++row)
    {
        uint8_t current_fret = start + row;

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
} // namespace io::guitar::six_strings