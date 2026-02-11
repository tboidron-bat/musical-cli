#include <array>
#include <cstddef>
#include <cstdint>

namespace musical::notation {
    
    constexpr char SHARP_ASCII = '#';
    constexpr char FLAT_ASCII  = 'b';

    constexpr char32_t SHARP_U32        = U'♯';
    constexpr char32_t FLAT_U32         = U'♭';
    constexpr char32_t DOUBLE_SHARP_U32 = U'𝄪';
    constexpr char32_t DOUBLE_FLAT_U32  = U'𝄫';
    constexpr char32_t NATURAL_U32      = U'♮';

    inline constexpr std::array<char, 7> NOTE_NAMES_SAXON =  
         { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };
}
