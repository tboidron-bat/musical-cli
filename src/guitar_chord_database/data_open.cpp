#include <musical/guitar_chord_database/data_open.h>

namespace chord::database
{

const diagram_map& database_open()
{
    using D = Diagram;

    constexpr uint8_t X = D::MUTE;

    static const diagram_map db =
    {
        // ========================
        // MAJEUR
        // ========================

        { "a:maj", {
            D({ X, 0, 2, 2, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            // x     0   0
            // =========== 
            // | | | | 1 |
            // | | 2 | | |
            // | 3 | | | |
        }},
        { "c:maj", {
            D({ X, 3, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
        }},
        { "d:maj", {
            D({ X, X, 0, 2, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D),
        }},
        { "e:maj", {
            D({ 0, 2, 2, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | |
            // 2 | | | | 4
        }},
        { "g:maj", {
            D({ 3, 2, 0, 0, 0, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},

        // ========================
        // MINEUR
        // ========================

        { "a:min", {
            D({ X, 0, 2, 2, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            // x     0   x 
            // =========== 
            // | | 1 | 1 | 
            // | | | | | |
            // | 3 | | | 3 
        }},
        { "c:min", {
            D({ X, 3, 1, 0, 1, X }, GuitarStandardTuning::A, D::CAGED::C),
        }},
        { "d:min", {
            D({ X, X, 0, 2, 3, 1 }, GuitarStandardTuning::D, D::CAGED::D),
        }},
        { "e:min", {
            D({ 0, 2, 2, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            // MINEUR 
            // x   0 0 0
            // =========== 
            // | 1 | | | |
            // | | | | | |
            // 2 | | | 3 4
        }},
        { "g:min", {
            D({ 3, 1, 0, 0, 3, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},

        // ========================
        // DOMINANT 7
        // ========================

        { "a:7", {
            D({ X, 0, 2, 0, 2, 0 }, GuitarStandardTuning::A, D::CAGED::A),
            // x         0 
            // =========== 
            // | | | | 1 | 
            // | | 2 | | |
            // | 3 | 3 | |
        }},
        { "c:7", {
            D({ X, 3, 2, 3, 1, 0 }, GuitarStandardTuning::A, D::CAGED::C),
        }},
        { "d:7", {
            D({ X, X, 0, 2, 1, 2 }, GuitarStandardTuning::D, D::CAGED::D),
        }},
        { "e:7", {
            D({ 0, 2, 0, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            // x   0 0 0
            // =========== 
            // | | | | | 1
            // | 2 | | | |
            // 3 | | | | |
        }},
        { "g:7", {
            D({ 3, 2, 0, 0, 0, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},

        // ========================
        // MIN7
        // ========================

        { "a:min:7", {
            D({ X, 0, 2, 0, 1, 0 }, GuitarStandardTuning::A, D::CAGED::A),
        }},
        { "d:min:7", {
            D({ X, X, 0, 2, 1, 1 }, GuitarStandardTuning::D, D::CAGED::D),
        }},
        { "e:min:7", {
            D({ 0, 2, 0, 0, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            //     0 0 
            // =========== 
            // | 1 | | | 2
            // | | | | | |
            // 3 | | | 4 |
        }},
        { "g:min:7", {
            D({ 3, 1, 0, 0, 3, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},

        // ========================
        // MAJ7
        // ========================

        { "c:maj:7M", {
            // CMAJ7 
            // x     0 0 0 
            // =========== 
            // | | | | | | 
            // | | 2 | | |
            // | 3 | | | |
            D({ X, 3, 2, 0, 0, 0 }, GuitarStandardTuning::A, D::CAGED::C),
        }},
        { "d:maj:7M", {
            D({ X, X, 0, 2, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D),
        }},
        { "e:maj:7M", {
            D({ 0, 2, 1, 1, 0, 0 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            //     0 0 0
            // =========== 
            // | | | | | |
            // | 1 | | | 3
            // 2 | | | | |
        }},
        { "g:maj:7M", {
            D({ 3, 2, 0, 0, 0, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},

        // ========================
        // AUTRES
        // ========================

        { "a:7:b5", {
            // x 0       x
            // ===========
            // | | 1 2 | |
            // | | | | 3 |
            // | | | | | |
            // | | | | | |
            D({ X, 0, 1, 1, 2, X }, GuitarStandardTuning::A, D::CAGED::A),
        }},
        { "d:add4", {
            // Dadd4(no5) (voicing ouvert atmosphérique)
            //     0 0 x x
            // =========== 
            //      .       
            //      .    
            //      .    
            // | 1 | | | | <-- 9 frette
            // 2 | | | | |
            D({ 10, 9, 0, 0, X, X }, GuitarStandardTuning::LOW_E, D::CAGED::G),
        }},
    };

    return db;
}

} // namespace chord::database