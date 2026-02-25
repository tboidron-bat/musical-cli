#pragma once

#include <musical/instruments/guitar/six_strings/ChordDiagram.h>
#include <musical/instruments/guitar/six_strings/database_shape_a.h>
#include <musical/instruments/guitar/six_strings/database_shape_c.h>
#include <musical/instruments/guitar/six_strings/database_shape_d.h>
#include <musical/instruments/guitar/six_strings/database_shape_e.h>
#include <musical/instruments/guitar/six_strings/database_shape_g.h>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_for_shape(ChordDiagram::CAGEDShape shape);

}