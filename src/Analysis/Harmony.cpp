#include <musical/Analysis/Harmony.h>

namespace musical {

/*===============================================================
  Degree
===============================================================*/

std::string Harmony::Degree::to_string() const {

    // std::cout << "[Harmony::" << __func__ << "]"
    //     << "\n  >>Var: _degree =" << to_string(_value)
    //     << "\n  >>Var: _accid =" << to_string(_accid)
    //     << std::endl;


    return to_string(_value) + to_string(_accid) + " " + _chord.to_string();
}

std::string Harmony::Degree::to_string(Value d) {
    switch(d) {
        case Value::I:   return "I";
        case Value::II:  return "II";
        case Value::III: return "III";
        case Value::IV:  return "IV";
        case Value::V:   return "V";
        case Value::VI:  return "VI";
        case Value::VII: return "VII";
    }
    return "";
}

std::string Harmony::Degree::to_string(Accid a) {
    switch(a) {
        case Accid::None:  
            return "";
        case Accid::Flat:  
            return "b";
        case Accid::Sharp: 
            return "#";
    }
    return "";
}

// flux
std::ostream& operator<<(std::ostream& os, const Harmony::Degree& d) {
    os << d.to_string() << " (" << d._mode.to_string() << ")";
    return os;
}
// JSON
void to_json(json& j, const Harmony::Degree& d) {
    j = json{
        {"degree", Harmony::Degree::to_string(d._value)},
        {"accid",  Harmony::Degree::to_string(d._accid)},
        {"chord",  d._chord.to_string()},
        {"mode",   d._mode.to_string()}
    };
}

void from_json(const json& j, Harmony::Degree& d) {

    std::string deg_str = j.at("degree").get<std::string>();

    if      (deg_str == "I")   d._value = Harmony::Degree::Value::I;
    else if (deg_str == "II")  d._value = Harmony::Degree::Value::II;
    else if (deg_str == "III") d._value = Harmony::Degree::Value::III;
    else if (deg_str == "IV")  d._value = Harmony::Degree::Value::IV;
    else if (deg_str == "V")   d._value = Harmony::Degree::Value::V;
    else if (deg_str == "VI")  d._value = Harmony::Degree::Value::VI;
    else if (deg_str == "VII") d._value = Harmony::Degree::Value::VII;

    std::string  acc_str = j.at("accid").get<std::string>();
    if(acc_str == "")       
        d._accid = Harmony::Degree::Accid::None;
    else if(acc_str == "b" || acc_str == "flat")      
        d._accid = Harmony::Degree::Accid::Flat;
    else if (acc_str == "#" || acc_str == "sharp" )      
        d._accid = Harmony::Degree::Accid::Sharp;

    // std::cout << std::endl << __func__ 
    //     << "\n  >>Var: degree =" << deg_str
    //     << "\n  >>Var: accid =" << acc_str        
    //     << std::endl;


    d._chord = ChordFactory::create(j.at("chord").get<std::string>());

    // std::cout  << __func__ 
    //     << "\n  >>Var: var_name =" << j.at("mode").get<std::string>()
    //     << std::endl;

    d._mode  = Mode(j.at("mode").get<std::string>());
}

/*===============================================================
  Harmony
===============================================================*/

Harmony& Harmony::operator+=(const Degree& d) {
    _progression.push_back(d);
    return *this;
}

// flux
std::ostream& operator<<(std::ostream& os, const Harmony& h) {
    for (const auto& d : h._progression) {
        os << d << " | ";
    }
    return os;
}

// JSON
void to_json(json& j, const Harmony& h) {
    j = json::array();
    for(const auto& d : h._progression) {
        j.push_back(d);
    }
}

void from_json(const json& j, Harmony& h) {
    h._progression.clear();
    for(const auto& item : j) {
        Harmony::Degree d;
        from_json(item, d);
        h += d;
    }
}

} // namespace musical
