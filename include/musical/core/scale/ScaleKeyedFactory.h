#pragma once

#include <string>
#include <array>

#include <musical/core/Pitch.h>
#include <musical/core/Intervals.h>
#include <musical/core/scale/ScalePattern.h>
#include <musical/core/scale/ScaleKeyed.h>

namespace musical::core::scale {

class ScaleKeyedFactory {

public:

    // ------------------------------------------------------------
    // From ScalePattern + Pitch
    // ------------------------------------------------------------
    static ScaleKeyed create(
        const ScalePattern&,
        const Pitch&,
        bool with_sharp = true
    );

    // ------------------------------------------------------------
    // Repeated interval generation
    // ------------------------------------------------------------
    static ScaleKeyed create(
        Interval interval,
        const Pitch& tonic,
        bool with_sharp = true
    );

    // ------------------------------------------------------------
    // Chromatic set generator
    // ------------------------------------------------------------
    static std::array<std::string,12> get_chromatique_set(
        bool with_sharp,
        const Pitch& note_begin
    );

};

} // namespace musical::core::scale