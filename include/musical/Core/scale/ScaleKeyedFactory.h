#pragma once

#include <string>
#include <musical/Core/scale/ScalePattern.h>
#include <musical/Core/scale/ScaleKeyed.h>
#include <musical/Core/note/Note.h>

namespace musical::core {

class ScaleKeyedFactory {

public:

    /*
     * Construire une gamme 
     * à partir d'une échelle et d'une note tonique.
     * @param ScalePattern  : l'échelle utilisée.     
     * @param Note   : la note tonique.
     * @param bsharp : écrit la gamme avec des dièses ou des bémols.
     */	
	static ScaleKeyed create(const ScalePattern&, const Note&, bool with_sharp=true);

    /**
     * Construit une gamme en répétant un intervalle fixe à partir d'une note tonique.
     *
     * @param interval   L'intervalle utilisé pour passer d'une note à la suivante.
     * @param Note       La note tonique (point de départ de la gamme).
     * @param with_sharp Si vrai, les notes sont nommées avec des dièses (ex : do#),
     *                   sinon avec des bémols (ex : réb).
     *
     * La génération s'arrête dès que l'on retombe sur la même note (même hauteur, modulo 12).
     *
     * @return Une ScaleKeyed construite à partir des sauts d'intervalle successifs.
     */
    static ScaleKeyed create(IntervalType interval, const Note& tonique, bool with_sharp = true);

    static std::array<std::string,musical::core::CHROMATIC_NOTE_COUNT> get_chromatique_set(
        bool bsharp,
        const Note& note_begin);    
};
}

