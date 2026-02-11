#include <musical/Core/scale/ScalePatternFactory.h>

#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace musical {

namespace {

const std::map<std::string, ScalePatternType> kStringToType = {
    // Base
    { "chromatic",    ScalePatternType::CHROMATIC },
    { "major",        ScalePatternType::MAJOR },
    { "minor",        ScalePatternType::MINOR },
    { "ionian",       ScalePatternType::IONIAN },
    { "aeolian",      ScalePatternType::AEOLIAN },

    // Modes
    { "dorian",       ScalePatternType::DORIAN },
    { "phrygian",     ScalePatternType::PHRYGIAN },
    { "lydian",       ScalePatternType::LYDIAN },
    { "mixolydian",   ScalePatternType::MIXOLYDIAN },
    { "locrian",      ScalePatternType::LOCRIAN },

    // Harmonic minor
    { "harmonic_minor",          ScalePatternType::HARMONIC_MINOR },
    { "locrian_natural_6",       ScalePatternType::LOCRIAN_NATURAL_6 },
    { "ionian_augmented",        ScalePatternType::IONIAN_AUGMENTED },
    { "dorian_sharp_4",          ScalePatternType::DORIAN_SHARP_4 },
    { "phrygian_dominant",       ScalePatternType::PHRYGIAN_DOMINANT },
    { "lydian_sharp_2",          ScalePatternType::LYDIAN_SHARP_2 },
    { "ultraphrygian",           ScalePatternType::ULTRAPHRYGIAN },
    { "superlocrian_diminished", ScalePatternType::SUPERLOCRIAN_DIMINISHED },

    // Jazz minor
    { "jazz_minor",        ScalePatternType::JAZZ_MINOR },
    { "dorian_flat2",      ScalePatternType::DORIAN_FLAT2 },
    { "lydian_augmented",  ScalePatternType::LYDIAN_AUGMENTED },
    { "lydian_dominant",   ScalePatternType::LYDIAN_DOMINANT },
    { "mixolydian_flat6",  ScalePatternType::MIXOLYDIAN_FLAT6 },
    { "aeolian_flat5",     ScalePatternType::AEOLIAN_FLAT5 },
    { "superlocrian",      ScalePatternType::SUPERLOCRIAN },

    // Pentatonic
    { "pentatonic_major",  ScalePatternType::PENTATONIC_MAJOR },
    { "pentatonic_minor",  ScalePatternType::PENTATONIC_MINOR },
    { "blues",             ScalePatternType::BLUES },

    // Exotic
    { "hungarian_major",   ScalePatternType::HUNGARIAN_MAJOR },
    { "hungarian_minor",   ScalePatternType::HUNGARIAN_MINOR },
    { "egyptian",          ScalePatternType::EGYPTIAN },
    { "arabic",            ScalePatternType::ARABIC },
    { "klezmer",           ScalePatternType::KLEZMER },
    { "hirajoshi",         ScalePatternType::HIRAJOSHI },
    { "chinese",           ScalePatternType::CHINESE }
};
} // namespace

const std::map<ScalePatternType, std::vector<int8_t>> ScalePatternFactory::s_scales = {

    // --- Base ---
        { ScalePatternType::CHROMATIC, {1,1,1,1,1,1,1,1,1,1,1,1} },
        { ScalePatternType::MAJOR,     {2,2,1,2,2,2,1} },
        { ScalePatternType::IONIAN,    {2,2,1,2,2,2,1} },
        { ScalePatternType::MINOR,     {2,1,2,2,1,2,2} },
        { ScalePatternType::AEOLIAN,   {2,1,2,2,1,2,2} },

    // --- Modes ---
        { ScalePatternType::DORIAN,     {2,1,2,2,2,1,2} },
        { ScalePatternType::PHRYGIAN,   {1,2,2,2,1,2,2} },
        { ScalePatternType::LYDIAN,     {2,2,2,1,2,2,1} },
        { ScalePatternType::MIXOLYDIAN, {2,2,1,2,2,1,2} },
        { ScalePatternType::LOCRIAN,    {1,2,2,1,2,2,2} },

    // --- Harmonic minor ---
        { ScalePatternType::HARMONIC_MINOR,        {2,1,2,2,1,3,1} },
        { ScalePatternType::LOCRIAN_NATURAL_6,     {1,2,2,1,3,1,2} },
        { ScalePatternType::IONIAN_AUGMENTED,      {2,2,1,3,1,2,1} },
        { ScalePatternType::DORIAN_SHARP_4,        {2,1,3,1,2,2,1} },
        { ScalePatternType::PHRYGIAN_DOMINANT,     {1,3,1,2,1,2,2} },
        { ScalePatternType::LYDIAN_SHARP_2,        {3,1,2,1,2,2,1} },
        { ScalePatternType::ULTRAPHRYGIAN,         {1,2,1,2,2,1,3} },
        { ScalePatternType::SUPERLOCRIAN_DIMINISHED,{2,1,2,2,1,3,1} },

    // --- Jazz minor ---
        { ScalePatternType::JAZZ_MINOR,        {2,1,2,2,2,2,1} },
        { ScalePatternType::DORIAN_FLAT2,      {1,2,2,2,2,1,2} },
        { ScalePatternType::LYDIAN_AUGMENTED,  {2,2,2,2,1,2,1} },
        { ScalePatternType::LYDIAN_DOMINANT,   {2,2,2,1,2,1,2} },
        { ScalePatternType::MIXOLYDIAN_FLAT6,  {2,2,1,2,1,3,1} },
        { ScalePatternType::AEOLIAN_FLAT5,     {2,1,2,1,3,1,2} },
        { ScalePatternType::SUPERLOCRIAN,      {1,2,1,2,2,2,2} },

    // --- Pentatonic ---
        { ScalePatternType::PENTATONIC_MAJOR,  {2,2,3,2,3} },
        { ScalePatternType::PENTATONIC_MINOR,  {3,2,2,3,2} },
        { ScalePatternType::BLUES,             {3,2,1,1,3,2} },

    // --- Exotic ---
        { ScalePatternType::HUNGARIAN_MAJOR,   {3,1,2,1,2,1,1} },
        { ScalePatternType::HUNGARIAN_MINOR,   {2,1,3,1,1,3,1} },
        { ScalePatternType::EGYPTIAN,          {2,1,4,1,4} },
        { ScalePatternType::ARABIC,            {1,3,1,2,1,3,1} },
        { ScalePatternType::KLEZMER,           {1,3,1,2,1,2,2} },
        { ScalePatternType::HIRAJOSHI,          {2,1,4,1,4} },
        { ScalePatternType::CHINESE,            {4,2,1,4,1} },
};    

ScalePattern ScalePatternFactory::create(ScalePatternType type) {

    if (s_scales.size() != static_cast<size_t>(ScalePatternType::__COUNT)) {
        throw std::logic_error(
            "ScalePatternType enum and ScalePatternFactory::s_scales are out of sync"
        );
    }

    auto it = s_scales.find(type);
    if (it == s_scales.end())
        throw std::out_of_range("ScalePatternFactory::create : unknown scale type");

    return ScalePattern(type, it->second);   
    
}
ScalePattern ScalePatternFactory::create(const std::string& name)
{
    std::string key = name;
    std::transform(key.begin(), key.end(), key.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    auto it = kStringToType.find(key);
    if (it == kStringToType.end())
        throw std::invalid_argument(
            "ScalePatternFactory::create : unknown scale name '" + name + "'"
        );

    return create(it->second);
}
std::vector<ScalePatternType> ScalePatternFactory::list_types() {
    std::vector<ScalePatternType> types;
    types.reserve(s_scales.size());

    for (const auto& [type, _] : s_scales) {
        types.push_back(type);
    }
    return types;
}

  

} // namespace musical