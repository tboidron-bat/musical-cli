#include <musical/instruments/guitar/six_strings/database_by_shape.h>

#include <stdexcept>

namespace musical::instruments::guitar::six_strings
{

const DiagramMap& database_for_shape(ChordDiagram::CAGEDShape shape)
{
    using SHAPE = ChordDiagram::CAGEDShape;

    switch (shape)
    {
        case SHAPE::A:
            return database_shape_a();

        case SHAPE::E:
            return database_shape_c();

        case SHAPE::C:
            return database_shape_d();

        case SHAPE::D:
            return database_shape_e();

        case SHAPE::G:
            return database_shape_g();
    }

    throw std::runtime_error("Unknown CAGED shape");
}

}