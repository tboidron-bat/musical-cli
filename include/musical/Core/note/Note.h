#pragma once

/**
* @brief Représente une note musicale dans le système anglo-saxon,
* incluant son nom (a–g), son altération (dièse, bémol...), son octave,
* et sa durée (Figure).
*/

#include <musical/Core/Figure.h> 
#include <musical/Core/MusicalCoreConstants.h>
#include <musical/Core/MusicalCoreEnums.h>

#include <cstdint> 
#include <ostream>

namespace musical {

class Note { //plutot SaxonNote

	friend class NoteFactory;
private:

    struct Pitch
    {
        char         _name;    
        Accidental   _accid;    
        uint8_t      _octave;   
    };

    struct Pitch _pitch;
    Figure       _figure; 
         
    Note(char name, Accidental accid, uint8_t octave = 4, Figure f = FigureType::QUARTER);

public:
    Note(const Note& other)
        : _pitch(other._pitch)
        , _figure(other._figure)
    {}

	bool operator==(const Note& other) const;

    /* --- Accesseurs --- */
    const Pitch& GetPitch() const { return _pitch;}
    const Figure& figure() const { return _figure; }

    /* --- Mutateurs --- */    
    void set_figure(const Figure& f) { _figure = f; }    
};

std::ostream& operator<<(std::ostream&, const Note&);
}