#include <musical/io/chord/out/stream.h>
#include <musical/io/note/out/stream.h>
#include <musical/Core/chord/Chord.h>
#include <musical/io/note/out/note_formatter.h>
#include <musical/analysis/chord/naming.h>

#include <ostream>
#include <sstream>
#include <cctype>


namespace musical::core
{
std::string capitalize(std::string s)
{
    if(!s.empty())
        s[0] = std::toupper(s[0]);

    return s;
}

namespace musical::core::chord
{
    std::ostream& operator<<(std::ostream& os, const Chord& chord)
    {
        std::string type =
            musical::analysis::chord::find_name(chord.type());

        if (type.empty())
            return os << "= ?";

        std::string tonique  = 
            musical::io::note::formatter::to_string(chord.root());

        os << capitalize(tonique) << type << "\n";

        const auto& intervals = chord.type().intervals();
        const auto pitches = chord.notes(true);

        os << "Notes     : ";

        for (const auto& p : pitches)
        {
            std::ostringstream tmp;
            tmp << p;
            os << capitalize(tmp.str()) << " ";
        }
        os << "\n";            
                
        os << 
            "Intervals : T ";

         for (const auto& i : intervals)
            os 
               << to_symbol(i) << " ";            

        os << "\n";                           
               
        return os;
    }
}
namespace musical::io::chord
{
    std::ostream& operator<<(std::ostream& os, lexeme_t::Category cat)
    {
        using C = lexeme_t::Category;

        switch (cat)
        {
            case C::TRIAD:       os << "TRIAD"; break;
            case C::SEVENTH:     os << "SEVENTH"; break;
            case C::EXTENSION:   os << "EXTENSION"; break;
            case C::ALTERATION:  os << "ALTERATION"; break;
            case C::SUSPENSION:  os << "SUSPENSION"; break;
            case C::ADDITION:    os << "ADDITION"; break;
            case C::SPECIAL:     os << "SPECIAL"; break;
            default:             os << "UNKNOWN"; break;
        }

        return os;
    }
}
