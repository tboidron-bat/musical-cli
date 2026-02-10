#pragma once
#include <musical/Core/Figure.h>

namespace musical {

class Rest {

public:
	Rest(Figure duration) : _figure(duration) {}

    Figure figure() const { return _figure; }

    std::string to_string() const;    

private:

    Figure _figure; // Durée de note (ronde, blanche, noire... pointée ...)
};
}