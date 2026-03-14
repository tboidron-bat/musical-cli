#pragma once

#include <musical/io/guitar/unicode/Grid.h>
#include <musical/guitar_chord_database/MovableShapeDiagram.h>

namespace io::guitar::unicode
{
class MovableDiagram : public Grid
{
public:

    MovableDiagram(const chord::database::MovableShapeDiagram& diagram);
};
}