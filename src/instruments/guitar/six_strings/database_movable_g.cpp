#include <musical/instruments/guitar/six_strings/database_movable_g.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const MovableDiagramMap& database_movable_g()
{
    constexpr uint8_t BASE = 0;

    using MSD = MovableShapeDiagram;
    using S   = MSD::string_state;
    using CT  = musical::core::chord::ChordType;
    using IT  = musical::core::IntervalType;

    static const MovableDiagramMap db =
    {
        // =========================================================
        // Forme G majeure
        // | | | | | |
        // 1 1 1 1 1 1 <-- fret number x
        // | | | 2 | |
        // | 4 3 | | |
        // | | | | | |
        // =========================================================
        {
            CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }),
            {
                MSD{
                    {
                        S::fretted(BASE + 3, 3),
                        S::fretted(BASE + 2, 2),
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 3, 4)
                    },
                    SixStringDiagram::GuitarString::LOW_E,
                    SixStringDiagram::CAGEDShape::G
                }
            }
        }
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings