#include <musical/chord_db/movable/extensions/maj9.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj9_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        // ========================================================
        // MAJ9 (1 3 5 7 9)
        // ========================================================
        {
            MAJ9,
            {
            }
        },

        // ========================================================
        // MAJ9 (sans quinte)
        // ========================================================
        {
            ( (1ULL << 4) | (1ULL << 11) | (1ULL << 14) ), // 3, 7, 9
            {
            }
        }
    };

    return db;
}

} // namespace chord::db