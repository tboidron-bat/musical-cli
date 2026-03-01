#include <musical/io/chord/output/stream.h>

#include <musical/io/note/output/stream.h>
#include <musical/Core/chord/Chord.h>
#include <ostream>

#include <musical/analysis/chord_name.h>


namespace musical::core::chord
{
    std::ostream& operator<<(std::ostream& os, const Chord& chord)
    {
        const auto candidates =
            musical::analysis::chord::find_name(chord);

        if (candidates.empty())
            return os << "= ?";

        os << candidates.front().name << " = ";

        const auto& intervals = chord.type().intervals();
        const auto pitches = chord.notes(true);

        // Tonique
        os << pitches[0] << " (tonique)";

        // Autres notes
        for (std::size_t i = 0; i < intervals.size(); ++i)
        {
            os << " + "
               << pitches[i + 1]
               << " ("
               << intervals[i]
               << ")";
        }

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
