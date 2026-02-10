#include <musical/Core/Rest.h>

using namespace musical;

std::string Rest::to_string() const {

	std::string res = "Silence de: " + _figure.to_string();
	return res;
}
