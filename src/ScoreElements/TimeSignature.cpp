#include <musical/ScoreElements/TimeSignature.h>
//#include "MeiTags.h"

#include <sstream>

using namespace musical;

TimeSignature::TimeSignature(uint8_t beats, BeatNoteType note_value)
    : 
    _beats_per_measure(beats), 
    _beat_note_value(note_value) {}

uint8_t TimeSignature::beats_per_measure() const {
    return _beats_per_measure;
}

BeatNoteType TimeSignature::beat_note_value() const {
    return _beat_note_value;
}

std::string TimeSignature::to_string(/*ToStringFlags flag*/) const 
{
    return std::to_string(_beats_per_measure) + "/" + std::to_string(static_cast<int>(_beat_note_value));

    /*switch(flag) {
        case ToStringFlags::SOLFEGE:
  
        case ToStringFlags::MEI:
            {
                std::string attrs = MeiTags::attr(MeiTags::ATTR_COUNT, std::to_string(_beats_per_measure)) + " " +
                                    MeiTags::attr(MeiTags::ATTR_UNIT, std::to_string(static_cast<int>(_beat_note_value)));
                return MeiTags::empty_tag_with_attrs("meter", attrs);
            }
        default:
            return "";
    }*/
}


