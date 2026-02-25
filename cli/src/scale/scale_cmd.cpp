#include <musical/Core/scale/ScalePatternFactory.h>
#include <musical/io/scale/scalepattern_formatter.h>

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc < 2 || argv[1] == std::string("--help"))
    {

        std::cerr << "usage: scale <tonic>[mode]\n";
        std::cerr << "example: scale C, scale Ddorian, scale A_harmonic_minor\n";

        return 0;
    }

    std::string symbol = argv[1];

    try
    {
        auto types = musical::core::scale::ScalePatternFactory::list_types();

        for (auto type : types)
        {
            std::cout
                << musical::io::scale::scalepattern_formatter::to_string(type)
                << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 2;
    }    
    catch (...)
    {
        std::cerr << "error: unknown exception\n";
        return 3;
    }

    return 0;
}