#pragma once

#include <cstdint>
#include <array>
#include <bitset>

namespace chord::database 
{
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

    enum class Style : uint16_t
    {
        NONE        = 0,
        CLASSICAL   = 1 << 0,
        FLAMENCO    = 1 << 1,
        ROCK        = 1 << 2,
        JAZZ        = 1 << 3,
        BLUES       = 1 << 4,
        FUNK        = 1 << 5,
        AMBIENT     = 1 << 6,
        PINKFLOYDIAN = 1 << 7,
        BRANDXIAN   = 1 << 8,
    };    

protected:
    GuitarString _root_string; // index de la corde ou se trouve la tonique            
    CAGEDShape _shape;
    uint16_t _style_mask = static_cast<uint16_t>(Style::NONE); // masque de styles (bitset) pour lesquels ce diagramme est pertinent

    SixStringDiagram(
        GuitarString root,
        CAGEDShape shape,
        uint16_t style_mask = static_cast<uint16_t>(Style::NONE)
    )
        : _root_string(root),
          _shape(shape),
          _style_mask(style_mask)
    {}

    virtual ~SixStringDiagram() = default;    

    virtual bool has_barre() const = 0 ;
    virtual std::size_t first_fret() const = 0;    
    virtual std::size_t nb_frets() const = 0;


public:
    GuitarString root_string() const { return _root_string; }
    CAGEDShape shape() const { return _shape; }
    
    bool has_style(Style s) const
    {
        return (_style_mask & static_cast<uint16_t>(s)) != 0;
    }
    bool has_any_style(uint16_t mask) const
    {
        return (_style_mask & mask) != 0;
    }    
    uint16_t style_mask() const
    {
        return _style_mask;
    }    
};
} //namespace chord::database