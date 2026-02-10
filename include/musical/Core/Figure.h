#ifndef __FIGURE_H__
#define __FIGURE_H__

#include <cstdint>
#include <string>

namespace musical {

enum class FigureType : uint16_t {
    LONGA            = 1,    // LONGA - 16 temps 
    BREVE            = 2,    // BREVE (BREVIS) - 8 temps
    WHOLE            = 4,    // RONDE
    HALF             = 8,    // BLANCHE
    QUARTER          = 16,   // NOIRE
    EIGHTH           = 32,   // CROCHE
    SIXTEENTH        = 64,   // DOUBLE CROCHE
    THIRTY_SECOND    = 128,  // TRIPLE CROCHE
    SIXTY_FOURTH     = 256   // QUADRUPLE CROCHE
};

class Figure {

private:
    FigureType _value;
    uint8_t _dots; // 0: simple, 1: pointée, 2: double-pointée, etc.

public:
    Figure(FigureType v = FigureType::QUARTER, uint8_t dots = 0)
        : _value(v), _dots(dots) {}

    bool operator==(const Figure& other) const {
        return this->_value     == other._value &&
               this->_dots    == other._dots;

    }        

    // Setters  
    void set_value(FigureType v) { _value = v; }

    //Getters
    FigureType value() const { return _value; }
    uint8_t dots() const { return _dots; }

    unsigned int duration() const;

    std::string to_string() const;

    //Ajoute un point (dot)
    void add_dot() { if (_dots < 3) ++_dots; }  // limite à 3 dots par exemple    
    void rem_dot() { _dots = 0; }  

    static  Figure from_mei(const std::string&,const std::string&);
};

}

#endif
