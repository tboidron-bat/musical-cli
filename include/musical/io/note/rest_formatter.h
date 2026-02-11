#pragma once

#include <string>
#include <musical/Core/note/Rest.h>

#include <musical/io/common/figure_formatter.h>

namespace musical::io::rest::formatter
{

    /**
     * @brief Returns a human-readable string representation.
     *
     * Example:
     *  "Silence de noire"
     *  "Silence de blanche pointée"
     */
    static std::string to_string(const musical::core::Rest& rest) {
        return "Silence de " +
           musical::io::formatter::to_string(rest.figure());
    }

}
