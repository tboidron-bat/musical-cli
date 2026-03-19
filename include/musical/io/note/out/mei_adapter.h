#include <string>

namespace musical::io::note {

    /**
    * Retourne le nom de la note dans le système latin
    * à partir d'une tonalité  MEI: "0","1s", ..., "3f", ..etc..
    */

    std::string from_mei(const std::string&);
}
