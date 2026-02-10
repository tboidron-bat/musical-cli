#pragma once

#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <unordered_map>
#include <functional>

#include <musical/Core/MusicalCoreEnums.h>

namespace musical::chord {

// chord_intervals = intervalles en demi-tons depuis la fondamentale
// - 0 est implicite (fondamentale)
// - ordre croissant
// ex : {4,7} = majeur, {3,7} = mineur
using chord_intervals = std::vector<IntervalType>;    


struct IntervalVectorHash
{
    size_t operator()(const chord_intervals& v) const noexcept
    {
        size_t h = 0;

        for (IntervalType iv : v)
        {
            h ^= std::hash<int>{}(static_cast<int>(iv))
               + 0x9e3779b9
               + (h << 6)
               + (h >> 2);
        }

        return h;
    }
};
}

namespace musical::chord::guitar {

template <size_t N_STRINGS>
class Diagram 
{
public:
    struct string_state
    {
        // --- valeurs spéciales pour fret ---
        static constexpr uint8_t MUTED  = 0xFF; // corde étouffée (X)
        static constexpr uint8_t UNUSED = 0xFE; // corde inutilisée (même pas à vide)

        // --- Corde de la guitare ---
        //musical::GuitarString _string;
        // --- 0 = à vide, >=1 = frette numéro ---
        uint8_t fret = UNUSED;    
        // --- 0 = pas de doigté, 1-4 = doigté ---      
        uint8_t finger = 0;
    };

    std::array<string_state,N_STRINGS> _strings;

    /* 
        frette correspond à la frette la plus basse utilisée dans le diagramme
            - si 0 : diagramme à partir du sillet */

    uint8_t _base_fret = 0;  



    Diagram(
        uint8_t base_fret,
        const std::array<string_state, N_STRINGS>& strings
    )
    : _strings(strings)
    , _base_fret(base_fret)
    {}
};

/*
    Base de données des diagrammes de guitare paramétrée
    par le nombre de cordes (N_STRINGS).

    Le template <N_STRINGS> permet de :
    - spécialiser la base de données selon le type d’instrument
      (guitare 6 cordes, 7 cordes, 12 cordes, etc.)
    - garantir à la compilation qu’un diagramme contient
      exactement N_STRINGS cordes
    - éviter de mélanger des diagrammes incompatibles
      (ex : 6 cordes dans une DB 7 cordes)

    Cette fonction ne contient aucune logique :
    elle expose simplement une base de données statique
    définie dans un fichier .cpp correspondant
    (ex : database<6>() dans chord_guitar_diagram_db_6.cpp).
*/

template <size_t N_STRINGS>
 const std::unordered_map<
     GuitarTuning,
     std::unordered_map<
         musical::chord::chord_intervals,
         std::vector<Diagram<N_STRINGS>>,
         musical::chord::IntervalVectorHash
     >
 >&
 database();

 }