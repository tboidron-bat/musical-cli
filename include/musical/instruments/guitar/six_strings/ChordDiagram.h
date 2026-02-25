#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <map>
#include <bitset>
#include <stdexcept>


namespace musical::instruments::guitar::six_strings {

struct barre_t
{
    uint8_t _fret;
    uint8_t _finger;
    std::bitset<6> strings; // indices des cordes concernées
};


class ChordDiagram
{

public:

    static constexpr std::size_t STRING_COUNT = 6;

    enum class CAGEDShape : int8_t
    {
        C,
        A,
        G,
        E,
        D
    };



    enum class GuitarString : uint8_t
    {
        LOW_E  = 0,  
        A      = 1,  
        D      = 2,  
        G      = 3,  
        B      = 4,  
        HIGH_E = 5   
    };    

    struct string_state
    {
        enum class State
        {
            UNUSED,
            MUTED,
            OPEN_STRING,  // corde à vide
            FRETTED
        };

        State _state = State::UNUSED;   
        uint8_t _fret = 0;     // valable si FRETTED             
        uint8_t _finger = 0;    // valable si FRETTED                 

    public:
        static string_state open_string()
        {
            return { State::OPEN_STRING, 0, 0 };
        }

        static string_state muted()
        {
            return { State::MUTED, 0, 0 };
        }

        static string_state fretted(uint8_t fret, uint8_t finger)
        {
            return { State::FRETTED, fret, finger };
        }    
        State state() const { return _state; }
        uint8_t fret() const { return _fret; }
        uint8_t finger() const { return _finger; }

    private:
        string_state(State s, uint8_t f, uint8_t finger)
            : _state(s), _fret(f), _finger(finger)
        {}        
    };



private:

    std::array<string_state, STRING_COUNT> _strings;
    GuitarString _root_string; // index de la corde ou se trouve la tonique            
    CAGEDShape _caged_shape;   

public:

    ChordDiagram(
        const std::array<string_state, STRING_COUNT>& strings
        , GuitarString root_string
        , CAGEDShape caged_shape
    )
        : _strings(strings)
        , _root_string(root_string)
        , _caged_shape(caged_shape)
    {
    }

    const std::array<string_state, STRING_COUNT>& strings() const
    {
        return _strings;
    }    
    GuitarString root_string() const { return _root_string; }    

    bool needs_fret_label() const
    {
        return first_fret() > 4;
    }
    bool is_open_chord() const
    {
        for (const auto& s : _strings)
        {
            if (s.state() == string_state::State::OPEN_STRING)
                return true;
        }
        return false;
    }
    bool has_barre() const;
    std::size_t first_fret() const;    
    std::size_t nb_frets() const;
};
} // namespace musical::instruments::guitar::six_string