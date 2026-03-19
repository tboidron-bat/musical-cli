#include <ostream>
#include <sstream>

#include <musical/io/chord/out/stream.h>
#include <musical/io/note/out/stream.h>

#include <musical/Core/chord/Chord.h>

#include <musical/io/note/out/note_formatter.h>

#include <musical/analysis/chord/naming.h>

namespace musical::core
{
    std::string interval_symbol(core::IntervalType it)
    {
        using I = core::IntervalType;

        switch (it)
        {
            case I::TONIQUE:                return "T";
            case I::SECONDE_MINEURE:        return "b2";
            case I::SECONDE_MAJEURE:        return "2";
            case I::TIERCE_MINEURE:         return "3m";
            case I::TIERCE_MAJEURE:         return "3M";
            case I::QUARTE_JUSTE:           return "4";
            case I::TRITON:                 return "b5";
            case I::QUINTE_JUSTE:           return "5";
            case I::SIXTE_MINEURE:          return "b6";
            case I::SIXTE_MAJEURE:          return "6";
            case I::SEPTIEME_MINEURE:       return "7";
            case I::SEPTIEME_MAJEURE:       return "7M";
            case I::OCTAVE:                 return "8";
            case I::NEUVIEME_MINEURE:       return "b9";
            case I::NEUVIEME_MAJEURE:       return "9";
            case I::ONZIEME:                return "11";
            case I::ONZIEME_AUGMENTEE:      return "#11";
            case I::TREIZIEME_MINEURE:      return "b13";
            case I::TREIZIEME_MAJEURE:      return "13";
            case I::QUATORZIEME_MINEURE:    return "14m";
            case I::QUATORZIEME_MAJEURE:    return "14M";
            case I::DOUBLE_OCTAVE:          return "2oct";
        }

        return "interval_symbol()==>?";
    }
}
#include <cctype>

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
               << interval_symbol(i) << " ";            

        os << "\n";                           
               
        return os;
    }
}
namespace musical::core
{
    std::ostream& operator<<(std::ostream& os, core::IntervalType it)
    {
        using I = core::IntervalType;

        switch (it)
        {
            case I::TONIQUE:                 return os << "tonique";
            case I::SECONDE_MINEURE:         return os << "seconde mineure";
            case I::SECONDE_MAJEURE:         return os << "seconde majeure";
            case I::TIERCE_MINEURE:          return os << "tierce mineure";
            case I::TIERCE_MAJEURE:          return os << "tierce majeure";
            case I::QUARTE_JUSTE:            return os << "quarte juste";
            case I::TRITON:                  return os << "triton";
            case I::QUINTE_JUSTE:            return os << "quinte juste";
            case I::SIXTE_MINEURE:           return os << "sixte mineure";
            case I::SIXTE_MAJEURE:           return os << "sixte majeure";
            case I::SEPTIEME_MINEURE:        return os << "septième mineure";
            case I::SEPTIEME_MAJEURE:        return os << "septième majeure";
            case I::OCTAVE:                  return os << "octave";
            case I::NEUVIEME_MINEURE:        return os << "neuvième mineure";
            case I::NEUVIEME_MAJEURE:        return os << "neuvième majeure";
            case I::DIXIEME_MAJEURE:         return os << "dixième majeure";
            case I::ONZIEME:                 return os << "onzième";
            case I::ONZIEME_AUGMENTEE:       return os << "onzième augmentée";
            case I::DOUZIEME:                return os << "douzième";
            case I::TREIZIEME_MINEURE:       return os << "treizième mineure";
            case I::TREIZIEME_MAJEURE:       return os << "treizième majeure";
            case I::QUATORZIEME_MINEURE:     return os << "quatorzième mineure";
            case I::QUATORZIEME_MAJEURE:     return os << "quatorzième majeure";
            case I::DOUBLE_OCTAVE:           return os << "double octave";
        }

        return os << "intervalle inconnu";
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
