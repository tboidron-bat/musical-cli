#pragma once

#include <string>

namespace chord::db {
    class MovableShapeDiagram;
}

namespace io::guitar::diagram::movable {

std::string to_ascii(

    const chord::db::MovableShapeDiagram& diagram);

}