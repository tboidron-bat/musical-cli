#pragma once
#include <musical/core/Figure.h>

namespace musical::core {

class Rest {

private:

    Figure _figure; // Durée de note (ronde, blanche, noire... pointée ...)

public:
	Rest(Figure f) : _figure(f) {}

    Figure figure() const { return _figure; }
};
}