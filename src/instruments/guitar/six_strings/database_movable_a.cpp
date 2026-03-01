#include <musical/instruments/guitar/six_strings/database_movable_a.h>
#include <musical/Core/intervals_defs.h>

namespace musical::instruments::guitar::six_strings
{

const MovableDiagramMap& database_movable_a()
{
    constexpr uint8_t BASE = 0;

    using MSD = MovableShapeDiagram;
    using S   = MSD::string_state;
    using CT  = musical::core::chord::ChordType;
    using IT  = musical::core::IntervalType;

    static const MovableDiagramMap db =
    {
        // =========================================================
        // Forme A majeure
        // | | | | | |
        // | 1 1 1 1 1 <-- fret number x
        // | | | | | |
        // | | 2 3 4 | 
        // | | | | | |
        // =========================================================
        {
            CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE }),
            {
                MSD{
                    std::array<S, SixStringDiagram::STRING_COUNT>{
                        S::muted(), 
                        S::fretted(BASE,  1),  
                        S::fretted(BASE+2,2),
                        S::fretted(BASE+2,3),
                        S::fretted(BASE+2,4),
                        S::fretted(BASE,  1)
                    },
                    SixStringDiagram::GuitarString::A,
                    SixStringDiagram::CAGEDShape::A
                }
            }
        },

        // =========================================================
        // Forme A mineure
        // |1|1|1|1|1| <-- fret number x
        // | | | |4| |
        // | |2|3| | |
        // | | | | | |
        // =========================================================

        // =========================================================
        {
            CT({ IT::TIERCE_MINEURE, IT::QUINTE_JUSTE }),
            {
                MSD{
                    std::array<S, SixStringDiagram::STRING_COUNT>{
                        S::muted(),
                        S::fretted(BASE,1),
                        S::fretted(BASE+2,3),
                        S::fretted(BASE+2,4),
                        S::fretted(BASE+1,2),
                        S::fretted(BASE,1)
                    },
                    SixStringDiagram::GuitarString::A,
                    SixStringDiagram::CAGEDShape::A
                }
            }
        },

        // =========================================================
        // Forme A7 (dominante)
        // Forme A majeure
        // |1|1|1|1|1| <-- fret number x
        // | | | | | |
        // | |2| |4| |
        // | | | | | |
        // =========================================================
        {
            CT({ IT::TIERCE_MAJEURE, IT::QUINTE_JUSTE, IT::SEPTIEME_MINEURE }),
            {
                MSD{
                    std::array<S, SixStringDiagram::STRING_COUNT>{
                        S::muted(),
                        S::fretted(BASE,1),
                        S::fretted(BASE+2,2),
                        S::fretted(BASE,1),
                        S::fretted(BASE+2,3),
                        S::fretted(BASE,1)
                    },
                    SixStringDiagram::GuitarString::A,
                    SixStringDiagram::CAGEDShape::A
                }
            }
        }
    };

    return db;
}

} // namespace musical::instruments::guitar::six_strings