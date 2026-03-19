#include <musical/guitar_chord_database/data_movable.h>

namespace chord::database
{

const movable_diagram_map& data_movable()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        { "maj", {

            // | | | | | |
            // | 1 1 1 1 1 
            // | | | | | |
            // | | 2 3 4 | 
            // | | | | | |
            D({ X, 0, 2, 2, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),

            // | | | | | |
            // | 1 1 1 1 1
            // | | | | 2 |
            // | | 3 | | |
            // | 4 | | | |
            D({ X, 3, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),

            // | | | | | |
            // | | 1 | | | 
            // | | | | | |
            // | | | 2 | 3
            // | | | | 4 |
            D({ X, X, 0, 2, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            
            // | | | | | |
            // 1 1 1 1 1 1 
            // | | | 2 | |
            // | 4 3 | | |
            // | | | | | |
            D({ 0, 2, 2, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),

            // | | | | | |
            // 1 1 1 1 1 1
            // | | | | | |
            // | 3 | | | |
            // 4 | | | | 2
            D({ 3, 2, 0, 0, 0, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G)            



        }},

        { "min", {
            // | 1 1 1 1 1
            // | | | | 4 |
            // | | 2 3 | |
            // | | | | | |
            D({ X, 0, 2, 2, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A)
        }},

        { "7", {
            // | 1 1 1 1 1 
            // | | | | | |
            // | | 2 | 4 |
            // | | | | | |
            D({ X, 0, 2, 0, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A)
        }},

        { "min:7", {
            // x         x 
            // | | 1 | 1 | 
            // | |   | | |
            // | 3 | 4 | |
            // | |   | | |                        
            D({ X, 3, 1, 3, 1, X }, GuitarStandardTuning::A, D::CAGED::C)
        }}
    };

    return db;
}

} // namespace chord::database