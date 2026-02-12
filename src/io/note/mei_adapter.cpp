#include <musical/io/note/mei_adapter.h>

#include <map>
#include <stdexcept>
#include <iostream>


namespace musical::io::note {

std::string from_mei(const std::string&n)
{
    std::map<std::string,std::string> mei_to_saxon
    {
        {"0",  "c"}, 
        {"1s", "g"},
        {"2s", "d"},
        {"3s", "a"},
        {"4s", "e"},
        {"5s", "b"},
        {"6s", "f#"},
        {"7s", "c#"},

        {"1f", "f"},
        {"2f", "bb"},
        {"3f", "eb"},
        {"4f", "ab"},
        {"5f", "db"},
        {"6f", "gb"},
        {"7f", "cb"}
    };

    auto it = mei_to_saxon.find(n);
    if (it != mei_to_saxon.end())
        return it->second;


    std::cerr << "[musical::NoteService::" << __func__ << "]" 
        << "string " << n << "not found in std::map" 
        << std::endl;

    throw std::invalid_argument("mei_to_saxon not found ");
}
}