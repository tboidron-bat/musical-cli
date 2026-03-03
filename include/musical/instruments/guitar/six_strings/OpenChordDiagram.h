#pragma once

#include <musical/instruments/guitar/six_strings/SixStringsDiagram.h>
#include <musical/Core/pitch_t.h>
#include <cstddef>

namespace musical::instruments::guitar::six_strings {

class OpenChordDiagram : public SixStringDiagram
{
public:

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

public:

    OpenChordDiagram(
        const std::array<string_state, STRING_COUNT>& strings
        , GuitarString root_string
        , CAGEDShape caged_shape
        , uint16_t style_mask = static_cast<uint16_t>(Style::NONE)
    )
        : SixStringDiagram(root_string, caged_shape,style_mask)
        , _strings(strings)
    {
    }

    const std::array<string_state, STRING_COUNT>& strings() const
    {
        return _strings;
    }    
    musical::core::pitch_t root_pitch() const; // calculé à partir de la corde de la tonique et du fret éventuel

    bool needs_fret_label() const
    {
        return first_fret() > 4;
    }
    bool has_barre() const override;
    std::size_t first_fret() const override;    
    std::size_t nb_frets() const override;
};
} // namespace musical::instruments::guitar::six_strings