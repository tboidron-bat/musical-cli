#pragma once

#include <musical/io/guitar/diagram/unicode/Grid.h>
#include <musical/instruments/guitar/six_strings/MovableShapeDiagram.h>

namespace io::guitar::diagram::unicode
{
namespace sst = musical::instruments::guitar::six_strings;

class Movable : public Grid
{
public:

    Movable(const sst::MovableShapeDiagram& diagram);
};
}