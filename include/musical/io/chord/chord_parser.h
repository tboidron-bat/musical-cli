#pragma once

#include <string>

namespace musical {
    class Chord;
}   

namespace musical::chord_parsing {


    /**
     * Parse un nom d’accord (notation anglo-saxonne)
     *
     * @param name Nom de l’accord ("Em", "F#7", "Bbmaj7", etc.)
     *
     */
    musical::Chord from_saxon_name(const std::string& );

} 
