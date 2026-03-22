#pragma once

#include <string>
#include <array>

#include <musical/Core/scale/ScalePattern.h>
#include <musical/Core/scale/ScaleKeyed.h>
#include <musical/Core/pitch_t.h>
#include <musical/Core/note/Note.h>
#include <musical/Core/Intervals.h>

namespace musical::core::scale {

class ScaleKeyedFactory {

public:

    // ------------------------------------------------------------
    // From ScalePattern + pitch_t (NEW - cleaner)
    // ------------------------------------------------------------
    static ScaleKeyed create(
        const ScalePattern&,
        const pitch_t&,
        bool with_sharp = true
    );

    // ------------------------------------------------------------
    // Repeated interval generation (pitch_t version - NEW)
    // ------------------------------------------------------------
    static ScaleKeyed create(
        Interval interval,
        const pitch_t& tonique,
        bool with_sharp = true
    );

    // ------------------------------------------------------------
    // Chromatic set generator
    // ------------------------------------------------------------
    static std::array<std::string,12> get_chromatique_set(
        bool with_sharp,
        const pitch_t& note_begin
    );

};

} // namespace musical::core::scale