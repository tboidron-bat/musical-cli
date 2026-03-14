#include <musical/guitar_chord_database/OpenChordDiagram.h>
#include <stdexcept>
#include <map>

namespace chord::database{


//fonction helper pour calculer la hauteur d'une corde à vide
musical::core::pitch_t pitch_for_string(const OpenChordDiagram::GuitarString& _root_string) 
{
    using namespace musical::core;    

    switch (_root_string) // ou string.number() selon ton API
    {
        case OpenChordDiagram::GuitarString::LOW_E: 
            return { NoteName::E, Accidental::NONE, 2 };
        case OpenChordDiagram::GuitarString::A: 
            return { NoteName::A, Accidental::NONE, 2 };            
        case OpenChordDiagram::GuitarString::D: 
            return { NoteName::D, Accidental::NONE, 3 }; 
        case OpenChordDiagram::GuitarString::G: 
            return { NoteName::G, Accidental::NONE, 3 }; 
        case OpenChordDiagram::GuitarString::B: 
            return { NoteName::B, Accidental::NONE, 3 }; 
        case OpenChordDiagram::GuitarString::HIGH_E: 
            return { NoteName::E, Accidental::NONE, 4 };
    }

    throw std::logic_error("Invalid guitar string index");
}
    
musical::core::pitch_t OpenChordDiagram::root_pitch() const
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
/*
    retourne la frette la plus basse utilisée dans le diagramme, 
    ou 0 si aucune frette n'est utilisée
*/
std::size_t OpenChordDiagram::first_fret() const
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

std::size_t OpenChordDiagram::nb_frets() const
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
bool OpenChordDiagram::has_barre() const
{
    for (std::size_t i = 0; i < STRING_COUNT; ++i)
    {
        const auto& a = _strings[i];

        if (a.state() != string_state::State::FRETTED)
            continue;

        int count = 1;

        for (std::size_t j = i + 1; j < STRING_COUNT; ++j)
        {
            const auto& b = _strings[j];

            if (b.state() == string_state::State::FRETTED &&
                b.fret() == a.fret() &&
                b.finger() == a.finger())
            {
                count++;
            }
        }

        if (count >= 2)
            return true;
    }

    return false;
}
}