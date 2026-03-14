#include <musical/guitar_chord_database/database_movable_d.h>
#include <musical/Core/intervals_defs.h>

namespace chord::database
{
const MovableDiagramMap& database_movable_d()
{
    constexpr uint8_t BASE = 0;

    using MSD = MovableShapeDiagram;
    using S   = MSD::string_state;
    using CT  = musical::core::chord::ChordType;
    using IT  = musical::core::IntervalType;

    static const MovableDiagramMap db =
    {
        // =========================================================
        // Forme D majeure
        // | | | | | |
        // | | 1 | | | <-- fret number x
        // | | | | | |
        // | | | 2 | 3
        // | | | | 4 |
        // =========================================================
        {
            CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }),
            {
                MSD{
                    {
                        S::muted(),
                        S::muted(),
                        S::fretted(BASE + 0, 1),
                        S::fretted(BASE + 2, 2),
                        S::fretted(BASE + 3, 4),
                        S::fretted(BASE + 2, 3)
                    },
                    SixStringDiagram::GuitarString::D,
                    SixStringDiagram::CAGEDShape::D
                }
            }
        }
    };

    return db;
}

} // namespace chord::database