#include <musical/instruments/guitar/six_strings/ChordDiagram.h>

namespace musical::instruments::guitar::six_strings{

std::size_t ChordDiagram::first_fret() const
{
    uint8_t min_fret = 255;
    bool has_fretted = false;

    for (const auto& sp : _strings)
    {
        if (sp.state() == string_state::State::FRETTED)
        {
            has_fretted = true;
            auto f = sp.fret();
            if (f < min_fret)
                min_fret = f;
        }
    }

    if (!has_fretted)
        return 0; // aucun doigt posé
    return static_cast<std::size_t>(min_fret);
}

std::size_t ChordDiagram::nb_frets() const
{
    uint8_t min_fret = 255;
    uint8_t max_fret = 0;
    bool has_fretted = false;
    for (const auto& sp : _strings)
    {
        if (sp.state() == string_state::State::FRETTED)
        {
            has_fretted = true;
            auto f = sp.fret();
            if (f < min_fret) min_fret = f;
            if (f > max_fret) max_fret = f;
        }
    }
    if (!has_fretted)
        return 0; // aucun doigt posé
    return static_cast<std::size_t>(max_fret - min_fret + 1);
}
bool ChordDiagram::has_barre() const
{
    std::map<std::pair<uint8_t,uint8_t>, int> counter;

    for (const auto& s : _strings)
    {
        if (s.state() == string_state::State::FRETTED)
        {
            auto key = std::make_pair(s.finger(), s.fret());
            counter[key]++;
        }
    }

    for (const auto& [key, count] : counter)
    {
        if (count >= 2)
            return true;
    }

    return false;
}
}