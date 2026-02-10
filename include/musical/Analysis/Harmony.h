#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <musical/Core/Mode.h>
#include <musical/Core/ChordFactory.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace musical {

class Harmony {

public:
    struct Degree {

        enum class Value { I=1, II, III, IV, V, VI, VII };
        enum class Accid { None, Flat, Sharp };

        Value _value;
        Accid _accid;
        Chord _chord;
        Mode _mode;

        Degree()
        : _value(Value::I), _accid(Accid::None),
          _chord(),
          _mode(Mode::ModeType::IONIAN) {}

        std::string to_string() const;

        // flux
        friend std::ostream& operator<<(std::ostream& os, const Degree& d);

        // JSON
        friend void to_json(json& j, const Degree& d);
        friend void from_json(const json& j, Degree& d);

        static std::string to_string(Value d);
        static std::string to_string(Accid a);
    };

private:
    Mode _mode;
    std::vector<Degree> _progression;

public:
    Harmony()
    : _mode(Mode::ModeType::IONIAN) 
    {}

    Harmony& operator+=(const Degree& d);

    // flux
    friend std::ostream& operator<<(std::ostream& os, const Harmony& h);


    // JSON
    friend void to_json(json& j, const Harmony& h);
    friend void from_json(const json& j, Harmony& h);

    const std::vector<Degree>& progression() const { return _progression; }
    void set_mode(const Mode& m) { _mode = m; }
    const Mode& mode() const { return _mode; }
};
}
