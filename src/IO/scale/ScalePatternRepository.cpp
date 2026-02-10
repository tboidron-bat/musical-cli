#include <musical/IO/scale/ScalePatternRepository.h>
#include <musical/IO/scale/scalepattern_formatter.h>

#include <tinyxml2.h>
#include <sstream>
#include <stdexcept>

namespace musical {

void ScaleRepository::loadFromFile(const std::string& path)
{
    //TODO: Implémenter le chargement depuis un fichier texte
    //# ~/.config/musical/scale.conf
    throw std::runtime_error("Not implemented");
}
void ScaleRepository::loadFromXmlFile(const std::string& xml_file_path)
{
    tinyxml2::XMLDocument xml_doc;
    if (xml_doc.LoadFile(xml_file_path.c_str()) != tinyxml2::XML_SUCCESS)
        throw std::runtime_error("Cannot load scale XML");

    auto* root = xml_doc.FirstChildElement("scales");
    if (!root)
        throw std::runtime_error("Missing <scales>");

    for (auto* e = root->FirstChildElement("scale"); e; e = e->NextSiblingElement("scale"))
    {
        const char* name = e->Attribute("name");
        const char* text = e->GetText();
        if (!name || !text) continue;

        // ScalePatternType type = ScalePattern::from_string(name);
        // if (type == ScalePatternType::UNKNOWN) continue;

        // std::vector<int> intervals;
        // std::stringstream ss(text);
        // int v;
        // while (ss >> v) intervals.push_back(v);

        // _intervals[type] = intervals;
    }
}
}


// bool ScalePattern::init(const std::string&xml_file_path)
// {
//     enum class XML_TAG {
//         SCALES, 
//         SCALE,
//         NAME
//     };

//     static const std::map<XML_TAG, std::string> xmltagtable = {

//             { XML_TAG::SCALES,  "scales"   },
//             { XML_TAG::SCALE,   "scale"    },
//             { XML_TAG::NAME,    "name"     }
//         };        


//     tinyxml2::XMLDocument xml_doc;
//     tinyxml2::XMLError r = xml_doc.LoadFile(xml_file_path.c_str());

//     if (r != tinyxml2::XML_SUCCESS) {

//         throw std::invalid_argument("Erreur chargement fichier XML : " + xml_file_path) ;
//         return false;
//     }

//     std::string x_balise = xmltagtable.at(XML_TAG::SCALES);

//     tinyxml2::XMLElement* root = xml_doc.FirstChildElement(x_balise.c_str());

//     if (!root) {

//         throw std::invalid_argument("Balise <scales> manquante dans : " + xml_file_path) ;        
//         return false;
//     }

//     x_balise = xmltagtable.at(XML_TAG::SCALE);

//     for (tinyxml2::XMLElement* scale_elem = root->FirstChildElement(x_balise.c_str());
//          scale_elem != nullptr;
//          scale_elem = scale_elem->NextSiblingElement(x_balise.c_str())) 
//     {
//         vector<int> degre_data;

//         const char* name       = scale_elem->Attribute("name");
//         const char* scale_data = scale_elem->GetText();

//         //std::cout <<  name << " " << scale_data << std::endl;        

//         if (!name || !scale_data) continue;

//         string sn = name;
//         stringstream ss(scale_data);
//         int val;
//         while (ss >> val) {
//             degre_data.push_back(val);
//         }

//         _resource[sn] = degre_data;

//     }
//     return true;
// }

