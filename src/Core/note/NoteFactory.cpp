#include <musical/Core/note/NoteFactory.h>

#include <algorithm>
#include <stdexcept>

#include <iostream>

namespace musical {

Note NoteFactory::create(int chromatic_value, uint8_t default_octave, Figure default_figure, bool sharp)
{
    /*Normaliser la valeur chromatique entre 0 et 11 */
    chromatic_value = chromatic_value % 12;


    static const std::array<unsigned int,7> no_acc_values = 
        { 0 , 2 ,  4 ,  5 ,  7 ,  9 ,  11 };


    static const std::array<char,7> base_names = {'c', 'd', 'e', 'f', 'g', 'a', 'b'};

    // Chercher si chromatic_value est une note naturelle (sans altération)
    auto it = std::find(no_acc_values.begin(), no_acc_values.end(), chromatic_value);

    if (it != no_acc_values.end())
    {
        // C'est une note naturelle
        size_t index = std::distance(no_acc_values.begin(), it);
        char name = base_names[index];
        return Note(name, musical::Accidental::NONE, default_octave, default_figure);        
    }

    // Sinon, c'est une note altérée
    if (sharp)     // Si sharp = true, on prend la note naturelle en dessous et on ajoute un dièse
    {
        int base_val = (chromatic_value + 11) % 12; // -1 modulo 12
        auto it_sharp = std::find(no_acc_values.begin(), no_acc_values.end(), base_val);
        if (it_sharp == no_acc_values.end())
            throw std::logic_error("NoteFactory: base note not found for sharp");
        size_t index = std::distance(no_acc_values.begin(), it_sharp);
        char name = base_names[index];
        return Note(name, musical::Accidental::SHARP, default_octave, default_figure);
    }
    else
    {
        int base_val = (chromatic_value + 1) % 12; // +1 modulo 12
        auto it_flat = std::find(no_acc_values.begin(), no_acc_values.end(), base_val);
        if (it_flat == no_acc_values.end())
            throw std::logic_error("NoteFactory: base note not found for flat");
        size_t index = std::distance(no_acc_values.begin(), it_flat);
        char name = base_names[index];
        return Note(name, musical::Accidental::FLAT, default_octave, default_figure);
    }                  
}


Note NoteFactory::create(char name,musical::Accidental accid,uint8_t octave, Figure figure)
{
    // On force la lettre en minuscule pour cohérence
    char n = static_cast<char>(std::tolower(static_cast<unsigned char>(name)));

    // Vérification minimale : doit être une lettre valide
    if (n < 'a' || n > 'g') {
        throw std::invalid_argument("[NoteFactory]::create: nom de note invalide");
    }

    return Note(n,accid,octave,figure);
}
Note NoteFactory::create(std::string name, uint8_t default_octave, 
    Figure default_figure)
{
    if (name.empty())
        throw std::invalid_argument("[NoteFactory::create] : Chaîne vide");

    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    char letter = name[0];

    /*Vérifie que la lettre est valide */
    auto it = std::find(NOTE_NAMES_SAXON.begin(), NOTE_NAMES_SAXON.end(), letter);

    if (it == NOTE_NAMES_SAXON.end()) {
        throw std::invalid_argument("[NoteFactory::create] Lettre de note invalide : " + std::string(name));
    }

    /*Détecte l'altération à partir du reste de la chaîne */
    using Acc = musical::Accidental;

    Acc accid = Acc::NONE;
    if (name.size() == 2) 
    {
        if (name[1] == SHARP_CHAR)
            accid = Acc::SHARP;
        else if (name[1] == FLAT_CHAR)
            accid = Acc::FLAT;
        else
            throw std::invalid_argument("[NoteFactory::create] Altération inconnue : " + name);
    } 
    else if (name.size() == 3) 
    {
        if (name[1] == FLAT_CHAR && name[2] == FLAT_CHAR)
            accid = Acc::DOUBLE_FLAT;
        else if (name[1] == SHARP_CHAR && name[2] == SHARP_CHAR)
            accid = Acc::DOUBLE_SHARP;        
        else
            throw std::invalid_argument("[NoteFactory::create] Altération multiple invalide : " + name);
    } 
    else if (name.size() > 3) 
    {
        throw std::invalid_argument("[NoteFactory::create] Chaîne trop longue pour une note anglo-saxonne : " + name);
    }

    return Note(letter, accid, default_octave, default_figure);
}
}