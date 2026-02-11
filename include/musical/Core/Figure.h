#pragma once

#include <cstdint>
#include <string>

namespace musical::core {

class Figure
{
public:

    // ================================
    // Valeur rythmique
    // ================================
    enum class Type : uint16_t
    {
        LONGA          = 1,
        BREVE          = 2,
        WHOLE          = 4,
        HALF           = 8,
        QUARTER        = 16,
        EIGHTH         = 32,
        SIXTEENTH      = 64,
        THIRTY_SECOND  = 128,
        SIXTY_FOURTH   = 256
    };

    // ================================
    // Points
    // ================================
    enum class Dot : uint8_t
    {
        NONE   = 0,
        ONE    = 1,
        TWO    = 2,
        THREE  = 3
    };

private:

    Type _type;
    Dot  _dots;

public:

    Figure(Type t = Type::QUARTER,
           Dot d = Dot::NONE)
        : 
        _type(t), 
        _dots(d)
    {}

    // ================================
    // Getters
    // ================================
    Type type() const noexcept { return _type; }
    Dot  dots() const noexcept { return _dots; }

    uint8_t dot_count() const noexcept
    {
        return static_cast<uint8_t>(_dots);
    }

    // ================================
    // Setters
    // ================================
    void set_type(Type t) noexcept { _type = t; }

    void set_dots(Dot d) noexcept { _dots = d; }

    void add_dot() noexcept
    {
        uint8_t value = dot_count();
        if (value < 3)
            _dots = static_cast<Dot>(value + 1);
    }

    void clear_dots() noexcept
    {
        _dots = Dot::NONE;
    }

    // ================================
    // Comparaison
    // ================================
    bool operator==(const Figure& other) const noexcept
    {
        return _type == other._type &&
               _dots == other._dots;
    }

    bool operator!=(const Figure& other) const noexcept
    {
        return !(*this == other);
    }

    /**
     * @brief Calcule la durée relative de la figure en unités internes.
     *
     * La valeur retournée est basée sur l'encodage interne des figures
     * (puissances de 2 : 1, 2, 4, 8, 16, 32, ...).
     *
     * Les points augmentent la durée selon la règle musicale standard :
     *   - 1 point  → + 1/2 de la valeur de base
     *   - 2 points → + 1/2 + 1/4
     *   - 3 points → + 1/2 + 1/4 + 1/8
     *
     * Exemple :
     *   QUARTER (16) pointée → 16 + 8 = 24
     *
     * @return Durée relative exprimée dans le système interne.
     *
     * @note Cette valeur n'est pas une durée absolue en temps réel,
     *       mais une représentation interne destinée aux calculs rythmiques.
     */

    unsigned int duration() const;
   

};

} 
