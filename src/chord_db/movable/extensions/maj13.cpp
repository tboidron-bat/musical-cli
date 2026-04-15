#include <musical/chord_db/movable/extensions/maj13.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj13_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        {
            (/*TRIAD_MAJ_NO5 |*/ (1ULL << 11) | (1ULL << 14) | (1ULL << 21)),
            {
            }
        }
    };

    return db;
}

}