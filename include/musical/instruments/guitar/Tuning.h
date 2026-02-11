#pragma once

#include <cstdint>

// enum class STANDARD {E_low,A,D,G,B,E_high};
// enum class DROP_D  { E_low,D,A,D,G,B,E_high};
// enum class OPEN_G  { D,G,D,G,B,E_high};
// enum class OPEN_D  { D,A,D,F#,A,D};
// enum class OPEN_E  { E,B,E,G#,B,E_high};
// enum class DADGAD  { D,A,D,G,A,D};

namespace musical::instrument::guitar {

    enum class TuningType : uint8_t {
        STANDARD,
        DROP_D,
        OPEN_G,
        OPEN_D,
        OPEN_E,
        DADGAD,
        COUNT
    };


class Tuning {
private:
    TuningType _type;

public:
    explicit Tuning(TuningType type)
        :
        _type(type) {}

    TuningType type() const noexcept { return _type; }        
};

}
