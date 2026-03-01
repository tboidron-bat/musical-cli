#pragma once

#include <cstdint>
#include <array>

#include <musical/Core/pitch_t.h>
#include <musical/instruments/guitar/six_strings/SixStringsDiagram.h>


namespace musical::instruments::guitar::six_strings {


//ex:   |1|1|1|1|1| <-- _base_fret
//      | | | | | |
//      | |2|3|4| | <-- offset
//      | | | | | |

class MovableShapeDiagram : public SixStringDiagram
{
public:
    struct string_state
    {
        enum class State
        {
            UNUSED,
            MUTED,
            FRETTED_OFFSET
        };
    private:        
        State _state = State::UNUSED;   
        uint8_t _fret_offset = 0;     // valable si FRETTED_OFFSET
        uint8_t _finger = 0;  

        constexpr string_state(State s, uint8_t offset, uint8_t finger)
            : _state(s), _fret_offset(offset), _finger(finger)
        {}
    public:

        static constexpr string_state unused()
        {
            return { State::UNUSED, 0, 0 };
        }
        static constexpr string_state muted()
        {
            return { State::MUTED, 0, 0 };
        }
        static constexpr string_state fretted(uint8_t offset, uint8_t finger)
        {
            return { State::FRETTED_OFFSET, offset, finger };
        }

        State state() const { return _state; }
        uint8_t offset() const { return _fret_offset; }
        uint8_t finger() const { return _finger; } 



    };        


private:

    std::array<string_state, SixStringDiagram::STRING_COUNT> _strings;

    uint8_t _base_fret = 0;    //


public:

    MovableShapeDiagram(
        const std::array<string_state, SixStringDiagram::STRING_COUNT>& strings
        , GuitarString root_string
        , CAGEDShape caged_shape
    )
        : SixStringDiagram(root_string, caged_shape)
        , _strings(strings)
    {
    }

    const std::array<string_state, SixStringDiagram::STRING_COUNT>& strings() const
    {
        return _strings;
    }    

    void place_root(const musical::core::pitch_t& root);    

    uint8_t base_fret() const { return _base_fret; }    

    bool has_barre() const override;
    std::size_t first_fret() const override;    
    std::size_t nb_frets() const override;

    
};
} // namespace musical::instruments::guitar::six_strings