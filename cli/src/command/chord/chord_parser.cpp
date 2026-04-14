#include <command/chord/chord_parser.h>

#include <musical/io/core/chord/parser/ChordLexer.h>
#include <musical/io/core/chord/parser/ChordParser.h>

#include <musical/chord_db/open/queries.h>
#include <musical/chord_db/movable/queries.h>

#include <Option.h>

#include <regex>

//#define DEBUG

namespace cli::command::chord
{
static void remove_option_from_cmd_line(std::string& cmd_line, const cli::command::Option& opt)
{
    std::string long_name  = "--" + opt.name();
    auto pos = cmd_line.find(long_name);
    if(pos != std::string::npos)
        cmd_line.erase(pos, long_name.length());            

    std::string short_name = "-"  + opt.short_name();                
    pos = cmd_line.find(short_name);
    if(pos != std::string::npos)
        cmd_line.erase(pos, short_name.length());
}
static void remove_option_parameters_from_cmd_line(std::string& cmd_line, const cli::command::Option& opt)
{
    for(std::size_t i = 0; i < opt.parameter_count(); ++i)
    { 
        if(opt.parameter(i)._provided)        
        {
            auto pos = cmd_line.find(opt.parameter(i)._value);                    
            if(pos != std::string::npos)                
                cmd_line.erase(pos, opt.parameter(i)._value.length());            
        }
    }
}
std::string chord_parser::from_input(const cli::chord::ChordCommand& cmd) 
{
#ifdef DEBUG
std::cout << "[chord_parser:: " << __func__ << "] raw input: <" << cmd.input_string() << ">\n";
#endif

    std::string cmd_line = cmd.input_string();

    for(const auto& opt : cmd.options())
    {
        if(opt->enabled())
        {            

#ifdef DEBUG
        std::cout << "[chord_parser:: " << __func__ << "] removing option: --" 
                  << opt->name() << " / -" 
                  << opt->short_name() << "\n";
#endif

            remove_option_from_cmd_line(cmd_line, *opt);   
            remove_option_parameters_from_cmd_line(cmd_line, *opt); 
        }
    }
#ifdef DEBUG
    std::cout << "cleaned command line: <" << cmd_line << ">\n";    
#endif
    cmd_line = std::regex_replace(cmd_line, std::regex("\\s+"), " ");
    return cmd_line;
}

void chord_parser::add_entries(cli::chord::ChordCommand& cmd)
{
    using musical::io::chord::ChordLexer;
    using musical::io::chord::ChordParser;

    auto cleaned = from_input(cmd);

    std::istringstream iss(cleaned);
    std::string token;

    cmd.entries().clear();

    while(iss >> token)
    {
        auto tokens = ChordLexer::tokenize(token);
        auto chord_opt = ChordParser::parse(tokens);    

        if(!chord_opt)
        {
            std::cerr << "Invalid chord symbol\n";
            continue;
        }

        const auto& chord = *chord_opt;

        auto mask = chord.type().intervals_mask();        

        // =========================
        // OPEN
        // =========================        
        auto open =
            ::chord::db::queries::open::find_diagrams(
                chord.tone(),
                mask
            );

        for(const auto& d : open)
        {
            cmd.entries().push_back({
                chord.tone(),
                mask,
                d
            });
        }
        // =========================
        // MOVABLE
        // =========================
        auto movable =
            ::chord::db::queries::movable::find_diagrams(mask);

        for(auto& d : movable)
        {
            d.place_root(static_cast<uint8_t>(chord.tone()));

            if (d.base_case() == 0)
                continue;

            cmd.entries().push_back({
                chord.tone(),
                mask,
                d
            });
        }
    }
}
}


// void diagram::add_diagrams(
//     ChordCommand& cmd,
//     const musical::core::chord::Chord& chord,
//     DiagramSource source,
//     std::optional<::chord::db::Diagram::CAGED> caged) const
// {
//     using namespace ::chord::db;

//     if (source == DiagramSource::Open)
//     {
//         // ============================================================
//         // OPEN
//         // ============================================================
//         auto diagrams = queries::open::find_diagrams(
//             chord.tone(),
//             chord.type().intervals_mask(),
//             caged);

//         for (const auto& d : diagrams)
//         {
//             cmd.entries().push_back({ chord.tone(), chord.type().intervals_mask(), d });
//         }
//     }
//     else
//     {
//         // ============================================================
//         // MOVABLE
//         // ============================================================
//         auto diagrams = queries::movable::find_diagrams(
//             chord.type().intervals_mask(),
//             caged);

//         for (auto d : diagrams)
//         {
//             d.place_root(static_cast<uint8_t>(chord.tone()));

//             if (d.base_case() == 0)
//                 continue;

//             cmd.entries().push_back({ chord.tone(), chord.type().intervals_mask(), d });
//         }
//     }
// }


//autre strategie pour clean
// std::vector<std::string> chord_tokens;

// for(int i = 1; i < argc; ++i)
// {
//     std::string tok = argv[i];

//     bool is_option = false;

//     for(const auto& opt : _options)
//     {
//         if(tok == opt->name() || tok == opt->short_name())
//         {
//             is_option = true;

//             int j = i + 1;

//             for(std::size_t p = 0; p < opt->parameter_count(); ++p)
//             {
//                 if(j >= argc)
//                     break;

//                 auto& param = opt->parameter(p);

//                 if(param.match_parameter(argv[j]))
//                 {
//                     param.parse(argv[j]);
//                     ++j;
//                 }
//                 else if(param._requirement ==
//                         option::parameter_t::Requirement::REQUIRED)
//                 {
//                     std::cerr << "Missing parameter\n";
//                 }
//             }

//             i = j - 1;
//             break;
//         }
//     }

//     if(!is_option)
//         chord_tokens.push_back(tok);
// }