#pragma once

#include <musical/io/guitar/unicode/GridCore.h>

namespace io::guitar::unicode
{
class MovableDiagram : public GridCore
{
public:

    MovableDiagram(const chord::database::MovableShapeDiagram& diagram);
};
}