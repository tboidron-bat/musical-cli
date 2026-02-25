#pragma once

#include <musical/Core/Figure.h> 
#include <cstdint> 

#include <musical/Core/pitch_t.h> 

namespace musical::core::note {
    
    class Factory;
}

namespace musical::core {

class Note {

public:

    friend class note::Factory;

private:


    pitch_t _pitch;
    Figure  _figure; 

    //using X = std::pair<struct Pitch, Figure>;
   
    Note(NoteName n, Accidental a, uint8_t o, Figure f)
        :
        _pitch{n, a, o}, _figure(f)
        {}

public:
    Note(const Note&) = default;    

	bool operator==(const Note& other) const noexcept;

    /* --- Accesseurs --- */

    //const Pitch& pitch() const { return _pitch;}

    NoteName name() const noexcept { return _pitch._name; }
    Accidental accidental() const noexcept { return _pitch._accidental; }
    uint8_t octave() const noexcept { return _pitch._octave; }


    const Figure& figure() const { return _figure; }
    Figure& figure() { return _figure; }


    /* --- Mutateurs --- */    

    void set_figure(const Figure& f) { _figure = f; }   
    
    /*--- Others ---*/
    std::size_t chromatic_index() const noexcept
    {
        return musical::core::chromatic_index(_pitch);
    }
};
}