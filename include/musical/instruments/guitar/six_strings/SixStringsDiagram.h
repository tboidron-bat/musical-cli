#pragma once

#include <cstdint>
#include <array>
#include <bitset>

namespace musical::instruments::guitar::six_strings {

class SixStringDiagram
{
public:

    struct barre_t
    {
        uint8_t _fret;
        uint8_t _finger;
        std::bitset<6> strings; // indices des cordes concernées
    };

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

protected:
    GuitarString _root_string; // index de la corde ou se trouve la tonique            
    CAGEDShape _shape;

    SixStringDiagram(
        GuitarString root,
        CAGEDShape shape
    )
        : _root_string(root),
          _shape(shape)
    {}

    virtual ~SixStringDiagram() = default;    

    virtual bool has_barre() const = 0 ;
    virtual std::size_t first_fret() const = 0;    
    virtual std::size_t nb_frets() const = 0;


public:
    GuitarString root_string() const { return _root_string; }
    CAGEDShape shape() const { return _shape; }
};
}