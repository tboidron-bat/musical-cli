#pragma once

#include <string>

namespace musical::instruments::guitar::six_strings {
    class MovableShapeDiagram;
}

namespace io::guitar::diagram::movable {

std::string to_ascii(

    const musical::instruments::guitar::six_strings::MovableShapeDiagram& diagram);

}