#include <musical/instruments/guitar/six_strings/database_movable_c.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const MovableDiagramMap& database_movable_c()
{
    constexpr uint8_t BASE = 0;

    using MSD = MovableShapeDiagram;
    using S   = MSD::string_state;
    using CT  = musical::core::chord::ChordType;
    using IT  = musical::core::IntervalType;

    static const MovableDiagramMap db =
    {
        // =========================================================
        // Forme C majeure
        // | | | | | |
        // | 1 1 1 1 1 <-- fret number x
        // | | | | 2 |
        // | | 3 | | |
        // | 4 | | | |
        // =========================================================
        {
            CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }),
            {
                MSD{
                    {
                        S::muted(),
                        S::fretted(BASE + 3, 4),
                        S::fretted(BASE + 2, 3),
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 1, 2),
                        S::fretted(BASE + 0, 1)
                    },
                    SixStringDiagram::GuitarString::A,
                    SixStringDiagram::CAGEDShape::C,
                    static_cast<uint16_t>(SixStringDiagram::Style::CLASSICAL)
                }
            }
        },
        // =========================================================
        // Cm7 (version partielle typique)
        // x         x 
        // =========== 
        // | | 1 | 1 | 
        // | |   | | |
        // | 3 | 4 | |
        //
        // =========================================================

        { CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }), {
            MSD{{ 
                S::muted(),
                S::fretted(BASE + 3,3),
                S::fretted(BASE + 1,1),
                S::fretted(BASE + 3,4),
                S::fretted(BASE + 1,1),
                S::muted()
            }, 
            SixStringDiagram::GuitarString::A,
            SixStringDiagram::CAGEDShape::C,
            static_cast<uint16_t>(SixStringDiagram::Style::BLUES) |
            static_cast<uint16_t>(SixStringDiagram::Style::JAZZ)}
        }}

    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings