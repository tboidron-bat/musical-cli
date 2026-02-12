#pragma once

#include <musical/Core/chord/Chord.h>

#include <string>
#include <optional>

namespace musical::io::chord {

// -----------------------------------------------------------------------------
// Création depuis un nom anglo-saxon (parser)
// -----------------------------------------------------------------------------
    /**
     * Parse un nom d’accord (notation anglo-saxonne)
     *
     * @param name Nom de l’accord ("Em", "F#7", "Bbmaj7", etc.)
     *
     */
    std::optional<core::Chord> 
    parse_from_saxon_name(const std::string& );

} 
