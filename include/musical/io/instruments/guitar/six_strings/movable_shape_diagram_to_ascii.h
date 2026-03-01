#pragma once

#include <string>

namespace musical::instruments::guitar::six_strings {
    class MovableShapeDiagram;
}

namespace io::guitar::six_strings {

std::string movable_shape_diagram_to_ascii(
    const musical::instruments::guitar::six_strings::MovableShapeDiagram& diagram);

}