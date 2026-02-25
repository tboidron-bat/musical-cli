#include <musical/Core/scale/ScaleKeyed.h>

namespace musical::core::scale {

// ------------------------------------------------------------
// operator+=
// ------------------------------------------------------------
ScaleKeyed& ScaleKeyed::operator+=(const pitch_t& pitch)
{
    _pitches.push_back(pitch);
    return *this;
}

} // namespace musical::core::scale