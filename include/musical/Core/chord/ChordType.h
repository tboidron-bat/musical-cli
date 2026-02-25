#pragma once

#include <vector>
#include <musical/Core/intervals_defs.h>
#include <algorithm>
#include <utility>

namespace musical::core::chord {

/**
 * @brief Structure intervallique d’un type d’accord.
 *
 * Représente un ensemble d’intervalles chromatiques relatifs
 * à une tonique implicite (non incluse).
 *
 * Les intervalles sont exprimés en demi-tons positifs.
 *
 * Exemple :
 *   m7 → {3, 7, 10}
 *
 * La tonique appartient à la classe Chord.
 */

    enum class ChordClassType {

        DYAD=2,     
        TRIAD,    
        TETRAD,   
        PENTAD,   
        HEXAD,    
        UNKNOWN
    };    


    
class ChordType
{
    // Les intervalles doivent être triés et uniques.
    std::vector<IntervalType> _intervals;
    
public:
    explicit ChordType(std::vector<IntervalType> intervals)
    {
        std::sort(intervals.begin(), intervals.end());
        intervals.erase(
            std::unique(intervals.begin(), intervals.end()),
            intervals.end()
        );
        _intervals = std::move(intervals);
    }

    /**
     * @brief Ordre strict faible basé sur la structure intervallique.
     *
     * Permet d’utiliser ChordType comme clé dans des conteneurs ordonnés
     * (ex: std::map).
     *
     * L’ordre est purement lexicographique et repose sur la comparaison
     * des vecteurs d’intervalles.
     *
     * Cet ordre n’a aucune signification musicale.
     */
    bool operator<(const ChordType& other) const
    {
        return _intervals < other._intervals;
    }
    bool operator==(const ChordType& other) const
    {
        return _intervals == other._intervals;
    }    

    ChordClassType class_type() const;


    // --- Accesseurs ---
    const std::vector<IntervalType>& intervals() const { return _intervals; }    
    std::size_t size() const;    
};

} 
