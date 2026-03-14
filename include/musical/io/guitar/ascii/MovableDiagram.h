#pragma once

#include <string>

namespace chord::database {
    class MovableShapeDiagram;
}

namespace io::guitar::diagram::movable {

std::string to_ascii(

    const chord::database::MovableShapeDiagram& diagram);

}