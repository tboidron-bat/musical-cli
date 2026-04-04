#include <musical/chord_db/movable/aug.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& aug_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // AUGMENTED TRIAD
        // ========================================================
        {
            TRIAD_AUG,
            {
            }
        },

        // ========================================================
        // AUG MAJ7 
        // ========================================================
        {
            (TRIAD_AUG | (1ULL << 11)),
            {

            }
        }
    };

    return db;
}

} // namespace chord::db