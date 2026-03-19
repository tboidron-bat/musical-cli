#pragma once

#include <cstdint>
#include <array>
#include <bitset>

// enum class GuitarChordStyle : uint16_t
// {
//     NONE         = 0,
//     CLASSICAL    = 1 << 0,
//     FLAMENCO     = 1 << 1,
//     ROCK         = 1 << 2,
//     JAZZ         = 1 << 3,
//     BLUES        = 1 << 4,
//     FUNK         = 1 << 5,
//     AMBIENT      = 1 << 6,
//     PINKFLOYDIAN = 1 << 7,
//     BRANDXIAN    = 1 << 8,
// };    

enum class GuitarStandardTuning : uint8_t { LOW_E  = 0, A = 1, D = 2, G = 3, B = 4, HIGH_E = 5 };


namespace chord::database 
{
class Diagram
{
public:

    static constexpr std::size_t STRING_COUNT = 6;

    enum class CAGED : int8_t { C, A, G, E, D };

    static constexpr uint8_t MUTE = 0xFF; //x
    static constexpr uint8_t UNUSED = 0xFF -1; //-        

private:
    uint8_t _base_case = 0; //== 0 --> Accord ouvert.

    std::array<uint8_t,STRING_COUNT> _strings{}; //Ex: [-x0232].

    GuitarStandardTuning _root_string; // index de la corde ou se trouve la tonique            
    CAGED _caged;
    
public:
    Diagram( 
        const std::array<uint8_t,STRING_COUNT>& strings,
        GuitarStandardTuning root_string,
        CAGED caged,
        uint8_t base_case = 0
    )
    : 
    _strings(strings),
    _root_string(root_string),
    _caged(caged),
    _base_case(base_case) {}

    std::size_t first_case() const;   
    std::size_t last_case() const;
    std::size_t nb_case() const;
    bool is_open() const;     

    //getters
    const std::array<uint8_t, STRING_COUNT>& strings() const { return _strings; }

    uint8_t root_note() const;
    void place_root(uint8_t);
    uint8_t base_case() const { return _base_case; }        

    GuitarStandardTuning root_string() const { return _root_string; }
    CAGED caged() const { return _caged; }
    };
} //namespace chord::database