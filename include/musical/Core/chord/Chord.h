#pragma once

#include <vector>
#include <musical/Core/note/Note.h>
#include <musical/Core/intervals_defs.h>

namespace musical::core {

    enum class ChordClassType {

        DYAD=2,     
        TRIAD,    
        TETRAD,   
        PENTAD,   
        HEXAD,    
        UNKNOWN
    };    




class Chord
{
private:
    core::Note _tonic;
    
    /* 
        Intervalles relatifs à la tonique, en demi-tons absolus :
        Exemple :
            Em7  -> {3, 7, 10}
            E13  -> {4, 7, 10, 14, 17, 21}
    */
    std::vector<IntervalType> _intervals;
    
public:
    Chord(Note tonic, std::vector<IntervalType> intervals)
        : _tonic(std::move(tonic))
        , _intervals(std::move(intervals))
    {}

    // --- Accesseurs ---
    const Note& tonic() const { return _tonic; }
    const std::vector<IntervalType>& intervals() const { return _intervals; }    
    const Figure& figure() const;
    std::size_t size() const;    

    // --- Mutateurs ---
    void set_figure(const Figure& f);


};

} 
