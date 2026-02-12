#pragma once

#include <string>
#include <musical/Core/chord/Chord.h>
#include <musical/Core/chord/common.h>
#include <musical/Core/scale/ScaleKeyed.h>

namespace musical::core{
    class Chord;
    class Note;
}

namespace musical::core::chord {

class Factory {

public:
    static Chord create(const Note& root, CommonType type);

    /* ---Crée un accord diatonique (dyade, triade, etc..) 
          à partir d'une note dans une gamme
    */
    static Chord create(
        const Note& root, 
        const musical::core::scale::ScaleKeyed& gamme, 
        ChordClassType nb_note=ChordClassType::TRIAD);
};
}

