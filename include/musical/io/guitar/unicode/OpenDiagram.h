#pragma once

#include <musical/io/guitar/unicode/Grid.h>
#include <musical/guitar_chord_database/OpenChordDiagram.h>

namespace io::guitar::unicode
{
class OpenDiagram : public Grid
{
public:
    OpenDiagram(const chord::database::OpenChordDiagram& diagram);
};
}