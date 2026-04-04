#include <command/chord/ChordCommand.h>
#include <Option.h>
#include <stream_option.h>

#include <command/chord/diagram_layout.h>

#include <command/chord/version_option.h>
#include <command/chord/help_option.h>
#include <command/chord/diagram_option.h>
#include <command/chord/random_option.h>
#include <command/chord/dumpdb_option.h>
#include <command/chord/play_option.h>
#include <command/chord/difficulty_option.h>
#include <command/chord/tuning_option.h>

#include <musical/io/core/chord/parser/ChordLexer.h>
#include <musical/io/core/chord/parser/ChordParser.h>
#include <musical/io/core/chord/ChordIO.h>
#include <musical/io/core/chord/out/naming.h>

#include <musical/io/chord_db/unicode/DiagramRenderer.h>

#include <sstream>
#include <regex>

//#define DEBUG

namespace cli::chord
{
ChordCommand::ChordCommand()
{
    _options.emplace_back(std::make_unique<version_option>(*this));
    _options.emplace_back(std::make_unique<help_option>(*this));
    _options.emplace_back(std::make_unique<dumpdb_option>(*this));
    _options.emplace_back(std::make_unique<random_option>(*this));
    _options.emplace_back(std::make_unique<diagram_option>(*this));
    _options.emplace_back(std::make_unique<play_option>(*this));
    _options.emplace_back(std::make_unique<difficulty_option>(*this));
    _options.emplace_back(std::make_unique<tuning_option>(*this));
}
int ChordCommand::run(int argc, char** argv)
{
    if(argc < 2)
    {
        print_usage();
        return 1;
    }

    _args.clear();

    for(int i = 0; i < argc; ++i)
        _args.emplace_back(argv[i]);

    for (auto& opt : _options)
        opt->parse(argc, argv);

    if(get_option<version_option>()->enabled())
        return get_option<version_option>()->execute();

    if(get_option<help_option>()->enabled())
        return get_option<help_option>()->execute();

    if(get_option<dumpdb_option>()->enabled())
        return get_option<dumpdb_option>()->execute();

    if(get_option<random_option>()->enabled())
    {
        get_option<random_option>()->execute();
    }        
    else
    {
        std::vector<musical::core::chord::Chord> chords = parse_chord();

        if(chords.empty())    
        {
            std::cerr << "Chord symbol required\n";        
            return 0;
        }            
    }

    if(get_option<diagram_option>()->enabled())        
        get_option<diagram_option>()->execute();

    if(get_option<play_option>()->enabled())        
        get_option<play_option>()->execute();

    render();

    return EXIT_SUCCESS;
}
std::string ChordCommand::chords_names_from_input() const
{
    std::string cmd_line;

    for(int i = 1; i < _args.size(); ++i)
    {
        cmd_line += _args[i];
        cmd_line += ' ';
    }

    if(!cmd_line.empty())
        cmd_line.pop_back();

#ifdef CHORD_COMMAND_DEBUG
    std::cout << "command line : <" << cmd_line << ">\n";    
#endif

    for(const auto& opt : _options)
    {
        if(opt->enabled())
        {            
            std::string long_name  = "--" + opt->name();
            auto pos = cmd_line.find(long_name);
            if(pos != std::string::npos)
                cmd_line.erase(pos, long_name.length());            

            std::string short_name = "-"  + opt->short_name();                
            pos = cmd_line.find(short_name);
            if(pos != std::string::npos)
                cmd_line.erase(pos, short_name.length());            


            for(std::size_t i = 0; i < opt->parameter_count(); ++i)
            { 
                if(opt->parameter(i)._provided)
                {
                    auto pos = cmd_line.find(opt->parameter(i)._value);                    
                    if(pos != std::string::npos)
                        cmd_line.erase(pos, opt->parameter(i)._value.length());            

                }
            
            }

        }
    }
#ifdef CHORD_COMMAND_DEBUG
    std::cout << "cleaned command line: <" << cmd_line << ">\n";    
#endif
    cmd_line = std::regex_replace(cmd_line, std::regex("\\s+"), " ");
    return cmd_line;
}
std::vector<musical::core::chord::Chord> 
ChordCommand::parse_chord()
{
    std::vector<musical::core::chord::Chord> chords;

    using musical::io::chord::ChordLexer;
    using musical::io::chord::ChordParser;

    chords.clear();    

    std::string cleaned = chords_names_from_input();

    std::istringstream iss(cleaned);
    std::string token;

    while(iss >> token)
    {
        auto tokens = ChordLexer::tokenize(token);
        auto chord_opt = ChordParser::parse(tokens);    

        if(chord_opt)
            chords.push_back(*chord_opt);
        else
            std::cerr << "Invalid chord symbol\n";

    }
    return chords;
}
static std::string make_name(
    musical::core::Tone tone,
    uint64_t mask)
{
    std::ostringstream oss;

    oss << tone;

    musical::core::chord::ChordType type(mask);

    return oss.str() + musical::io::chord::to_string(type);
}
void ChordCommand::render() const
{
    if(_entries.empty())
    {
        std::cerr << "No diagrams to display\n";
        return;
    }

    Layout layout(terminal::get_width());

    for(const auto& d : _entries)
    {
        std::string name = make_name(d._root, d._intervals_mask);
        layout.add_block(
            io::chord::db::unicode::DiagramRenderer::render(d._diagram,name)
        );
    }

    std::cout << layout.render();
}
void ChordCommand::print_name() const
{
    std::cout << "Chord CLI — version 0.3.0";
}
void ChordCommand::print_usage() const 
{
    std::cout << "Usage:\n";
    std::cout << "\tchord [options] <symbol>\n";
    std::cout << "Try:\n";
    std::cout << "\tchord --help\n";
}        

void ChordCommand::print_help() const
{
    std::cout << "Options:\n";

    for (const auto& opt : _options)
        std::cout << *opt;
}
} // namespace cli::chord

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