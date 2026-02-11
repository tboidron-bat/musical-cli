#pragma once

namespace musical {
    class Chord;
}   

namespace musical::analysis::Chord {


    bool is_minor(const musical::Chord& chord);
    bool is_major(const musical::Chord& chord);

    bool has_seventh(const musical::Chord& chord);

}





