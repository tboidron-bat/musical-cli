#include <musical/instruments/guitar/six_strings/ChordDiagram.h>
#include <stdexcept>

namespace musical::instruments::guitar::six_strings{


//fonction helper pour calculer la hauteur d'une corde à vide
musical::core::pitch_t pitch_for_string(const ChordDiagram::GuitarString& _root_string) 
{
    using namespace musical::core;    

    switch (_root_string) // ou string.number() selon ton API
    {
        case ChordDiagram::GuitarString::LOW_E: 
            return { NoteName::E, Accidental::NONE, 2 };
        case ChordDiagram::GuitarString::A: 
            return { NoteName::A, Accidental::NONE, 2 };            
        case ChordDiagram::GuitarString::D: 
            return { NoteName::D, Accidental::NONE, 3 }; 
        case ChordDiagram::GuitarString::G: 
            return { NoteName::G, Accidental::NONE, 3 }; 
        case ChordDiagram::GuitarString::B: 
            return { NoteName::B, Accidental::NONE, 3 }; 
        case ChordDiagram::GuitarString::HIGH_E: 
            return { NoteName::E, Accidental::NONE, 4 };
    }

    throw std::logic_error("Invalid guitar string index");
}
    
musical::core::pitch_t ChordDiagram::root_pitch() const
{
    using namespace musical::core;

    std::size_t index =
        static_cast<std::size_t>(_root_string);

    const string_state& state = _strings[index];

    if (state.state() == string_state::State::MUTED
        || state.state() == string_state::State::UNUSED)
    {
        throw std::logic_error("Root string is not playable");
    }

    pitch_t pitch = pitch_for_string(_root_string);

    if(state.state() != string_state::State::OPEN_STRING)
        pitch += state.fret(); // fonctionne si operator+= est correct

    return pitch;
}

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