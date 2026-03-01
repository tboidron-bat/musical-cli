#include <musical/instruments/guitar/six_strings/database_movable_e.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const MovableDiagramMap& database_movable_e()
{
    constexpr uint8_t BASE = 0;

    using MSD = MovableShapeDiagram;
    using S   = MSD::string_state;
    using CT  = musical::core::chord::ChordType;
    using IT  = musical::core::IntervalType;

    static const MovableDiagramMap db =
    {
        // =========================================================
        // Forme E majeure
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
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 2, 3),
                        S::fretted(BASE + 2, 4),
                        S::fretted(BASE + 1, 2),
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 0, 1)
                    },
                    SixStringDiagram::GuitarString::LOW_E,
                    SixStringDiagram::CAGEDShape::E
                }
            }
        }
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings