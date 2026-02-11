#pragma once

#include <string>
#include <algorithm>

#include <musical/Core/scale/ScalePattern.h>
#include <musical/Core/MusicalCoreEnums.h>

namespace musical {

/**
 * @brief Classe spécialisée représentant les 7 modes diatoniques.
 * 
 * Hérite de ScalePattern pour réutiliser les intervalles et ressources.
 */
class Mode : public ScalePattern {

public:
    enum class ModeType {
        IONIAN,
        DORIAN,
        PHRYGIAN,
        LYDIAN,
        MIXOLYDIAN,
        AEOLIAN,
        LOCRIAN,
        UNKNOWN
    };

    /// Constructeur depuis un ModeType
    explicit Mode(ModeType m);

    /// Constructeur depuis une string (ex: "dorian")
    explicit Mode(const std::string& name);

    /// Accès direct au type de mode
    ModeType mode() const { return _mode; }

    /// Conversion en string (anglais)
    //std::string to_string() const;

    /// Conversion en français
    //std::string to_french() const;

public:
    /// Convertit ModeType -> ScalePatternType
    static ScalePatternType to_scale_type(ModeType m);

    /// Convertit string -> ModeType
    static ModeType from_string(const std::string& s);

private:
    ModeType _mode;
};
} 
