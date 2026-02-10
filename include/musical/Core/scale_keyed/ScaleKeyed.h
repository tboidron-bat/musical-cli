#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <musical/Core/note/Note.h>

namespace musical {

class ScaleKeyed {

    friend class ScaleKeyedFactory;

public:

    // Itérateurs permettant de parcourir la gamme
	using iterator = std::vector<Note>::iterator;
    using const_iterator = std::vector<Note>::const_iterator;    

   /// Début et fin pour itération non-const
    iterator begin() { return _notes.begin(); }
    iterator end() { return _notes.end(); }

    /// Début et fin pour itération const
    const_iterator begin() const { return _notes.begin(); }
    const_iterator end()   const { return _notes.end(); }    
    
    // opérateur d’assignation
    ScaleKeyed& operator=(const ScaleKeyed& other) {
        if (this != &other) {
            _notes = std::vector<Note>(other._notes.begin(), other._notes.end());
        }
        return *this;
    }

    /**
     * @brief Accès direct à une note par index.
     * @param index Position de la note dans la gamme
     * @return Référence modifiable à la note
     */    
    Note& operator[](std::size_t index) { return _notes[index]; }  

    /**
     * @brief Accès direct en lecture à une note par index.
     * @param index Position de la note dans la gamme
     * @return Référence const à la note
     */
    const Note& operator[](size_t index) const { return _notes[index]; } 

    /**
     * @brief Ajoute une note à la gamme.
     */
    ScaleKeyed& operator+=(Note&);

    ScaleKeyed& operator+=(const Note& note);


    /**
     * @brief Supprime la dernière note de la gamme si elle n’est pas vide.
     */
    void pop_back() {
        if (!_notes.empty())
            _notes.pop_back();
    }

    /**
     * Retourne une nouvelle gamme obtenue en effectuant une rotation 
     * de la gamme courante selon l’intervalle donné.
     * 
     * Par exemple, pour la gamme de base : do, ré, mi, fa, sol, la, si, do
     * et l’intervalle SECONDE_MINEURE, la méthode retourne :
     * ré, mi, fa, sol, la, si
     */
    //ScaleKeyed rotate(IntervalType) const; 

    /**
     * @brief Représentation textuelle de la gamme.
     * @return Chaîne contenant la liste des notes de la gamme
     */
	std::string to_string() const;

    std::size_t size() const { return _notes.size(); }
    void truncate(std::size_t n) {
        while (_notes.size() > n) {
            _notes.pop_back();
        }
}   

private:
    std::vector<Note> _notes;    
};
}


