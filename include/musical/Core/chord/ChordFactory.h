#pragma once

#include <string>
#include <musical/Core/MusicalCoreEnums.h>

namespace musical{
    class Chord;
    class Note;
    class ScaleKeyed;
}

namespace musical {

class ChordFactory {

public:
    static Chord create(const Note& root, CommonChordType type);

    /* ---Crée un accord diatonique (dyade, triade, etc..) 
          à partir d'une note dans une gamme
    */
    static Chord create(const Note& root, 
                        const ScaleKeyed& gamme, 
                        ChordClassType nb_note=ChordClassType::TRIAD);

    //static Chord create(const std::vector<Note>&);

    static Chord create(const std::string& name_en);

};
}

