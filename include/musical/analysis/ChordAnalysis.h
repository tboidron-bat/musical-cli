#pragma once

namespace musical::core {
    class Chord;
}   

namespace musical::analysis::Chord {


    bool is_minor(const core::Chord& chord);
    bool is_major(const core::Chord& chord);

    bool has_seventh(const core::Chord& chord);

}





