#ifndef __TIMESIGNATURE_H__
#define __TIMESIGNATURE_H__

#include <string>
#include <cstdint>

namespace musical {

enum class BeatNoteType : uint8_t {

    WHOLE         = 1,    // ronde
    HALF          = 2,    // blanche
    QUARTER       = 4,    // noire
    EIGHTH        = 8,    // croche
    SIXTEENTH     = 16,   // double croche
    THIRTY_SECOND = 32,   // triple croche 
    SIXTY_FOURTH  = 64    // quadruple croche 
};

class TimeSignature {

private:
    uint8_t _beats_per_measure;  // nombre de temps par mesure (numérateur)
    BeatNoteType _beat_note_value;    // valeur de la note qui vaut 1 temps (dénominateur)

public:

    TimeSignature(uint8_t beats = 4, 
                  BeatNoteType note_value = BeatNoteType::QUARTER);

    // Accesseurs
    uint8_t beats_per_measure() const;
    BeatNoteType beat_note_value() const;

    //enum class ToStringFlags { SOLFEGE, MEI };

    // Renvoie la signature rythmique sous forme de chaîne (ex: "4/4")
    // oou au format MEI.
    std::string to_string(/*ToStringFlags flag=ToStringFlags::SOLFEGE*/) const;
};

} // namespace musical

#endif
