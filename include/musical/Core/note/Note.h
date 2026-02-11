#pragma once

#include <musical/Core/Figure.h> 
#include <cstdint> 

namespace musical::core::note {
    
    class Factory;
}

namespace musical::core {

class Note {

public:
    enum class Name : uint8_t {

        C,D,E,F,G,A,B
    };

    enum class Accidental { 
        
        NONE, SHARP, FLAT, DOUBLE_SHARP, DOUBLE_FLAT 
    };    

    friend class note::Factory;

private:

    struct Pitch
    {
        Name         _name;    
        Accidental   _accid;    
        uint8_t      _octave;   
    };

    struct Pitch _pitch;
    Figure       _figure; 

    //using X = std::pair<struct Pitch, Figure>;
   
    Note(Name n, Accidental a, uint8_t o, Figure f)
        :
        _pitch{n, a, o}, _figure(f)
        {}

public:
    Note(const Note&) = default;    

	bool operator==(const Note& other) const noexcept;

    /* --- Accesseurs --- */

    //const Pitch& pitch() const { return _pitch;}

    Name name() const noexcept { return _pitch._name; }
    Accidental accidental() const noexcept { return _pitch._accid; }
    uint8_t octave() const noexcept { return _pitch._octave; }


    const Figure& figure() const { return _figure; }
    Figure& figure() { return _figure; }


    /* --- Mutateurs --- */    

    void set_figure(const Figure& f) { _figure = f; }   
    
    /*--- Others ---*/
    std::size_t chromatic_index() const noexcept;     
};

    //std::ostream& operator<<(std::ostream&, const Note&);
}