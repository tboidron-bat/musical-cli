#include <command/chord/ChordCommand.h>
#include <Option.h>
#include <stream_option.h>

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

#include <sstream>
#include <regex>

//#define CHORD_COMMAND_DEBUG

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
        parse_chord(argc,argv);
    }

    if(_chords.empty())    
    {
        std::cerr << "Chord symbol required\n";        
        return 0;
    }            

    if(get_option<diagram_option>()->enabled())        
        get_option<diagram_option>()->execute();
    else
    {
        for(const auto& c : _chords)
            std::cout << c << "\n";           
    }            
    if(get_option<play_option>()->enabled())        
        get_option<play_option>()->execute();

    return EXIT_SUCCESS;
}
std::string ChordCommand::clean(int argc, char**argv)
{
    std::string cmd_line;

    for(int i = 1; i < argc; ++i)
    {
        cmd_line += argv[i];
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
int ChordCommand::parse_chord(int argc, char**argv)
{
    using musical::io::chord::ChordLexer;
    using musical::io::chord::ChordParser;

    _chords.clear();    

    std::string cleaned = clean(argc, argv);

    std::istringstream iss(cleaned);
    std::string token;

    while(iss >> token)
    {
        auto tokens = ChordLexer::tokenize(token);
        auto chord_opt = ChordParser::parse(tokens);    

        if(chord_opt)
            _chords.push_back(*chord_opt);
        else
            std::cerr << "Invalid chord symbol\n";

    }
    return 1;
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