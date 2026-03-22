#include <musical/guitar_chord_database/data_movable.h>

namespace chord::database
{

using movable_diagram_map =
std::map<std::string,std::vector<Diagram>>;

const movable_diagram_map& data_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;    
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        { "maj", //interval_mask = 10010000
            {
            
            // | 1 1 1 1 1 
            // | | | | | |
            // | | 2 3 4 | 
            // | | | | | |
            D({ X, BASE, 2, 2, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A),

            // | | | | | |
            // | 1 1 1 1 1
            // | | | | 2 |
            // | | 3 | | |
            // | 4 | | | |
            D({ X, 3, 2, BASE, 1, BASE }, GuitarStandardTuning::A, D::CAGED::C),

            // x x
            // | | 1 | | | 
            // | | | | | |
            // | | | 2 | 3
            // | | | | 4 |
            D({ X, X, BASE, 2, 3, 2 }, GuitarStandardTuning::D, D::CAGED::D),
            
            // | | | | | |
            // 1 1 1 1 1 1 
            // | | | 2 | |
            // | 4 3 | | |
            // | | | | | |
            D({ BASE, 2, 2, 1, BASE, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::E),

            // | | | | | |
            // 1 1 1 1 1 1
            // | | | | | |
            // | 2 | | | |
            // 3 | | | | 4
            D({ 3, 2, BASE, BASE, BASE, 3 }, GuitarStandardTuning::LOW_E, D::CAGED::G)            
            }
        },

        { "min", 
            {
            // | 1 1 1 1 1
            // | | | | 4 |
            // | | 2 3 | |
            // | | | | | |
            D({ X, BASE, 2, 2, 1, BASE }, GuitarStandardTuning::A, D::CAGED::A)
            }
        },
        { "maj:7", 
            {
            // | 1 1 1 1 1 
            // | | | | | |
            // | | 2 | 4 |
            // | | | | | |
            D({ X, BASE, 2, BASE, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A)
            }
        },
        { "min:7", 
            {
            // x          
            // | 1 1 1 1 1 
            // | | | | | |
            // | 2 | 3 | 4
            // | | | | | |                        
            D({ X, 2, BASE, 2, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::C)
            }
        },
        { "min:7:no5", 
            {
            // x         x 
            // | | 1 | 2 | 
            // | |   | | |
            // | 3 | 4 | |
            // | |   | | |                        
            D({ X, 2, BASE, 2, BASE, X }, GuitarStandardTuning::A, D::CAGED::C)
            }
        },
        { "maj:7M:#4", 
            {
            //           x
            // 1 1 1 1 1 |
            // | 2 3 4 | |
            // | | | | | |
            // | | | | | |                        
            D({ BASE, 1, 1, 1, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::E)
            }
        },
        { "maj:7M:#4:/5", 
            {
            //           
            // 1 1 | | | 1
            // | | 2 3 | |
            // | | | | 4 |
            // | | | | | |                        
            D({ BASE, BASE, 2, 3, 4, BASE }, GuitarStandardTuning::A, D::CAGED::A),
            // x          
            // | | | | 1 1
            // | | | | | |
            // | | | 2 | |
            // | 3 4 | | |                        
            D({ X, 3, 3, 2, BASE, BASE }, GuitarStandardTuning::D, D::CAGED::E) //D::CAGED::E & G
            }
        },   
        { "maj:7M:#4:/3", 
            // mask = (1<<4 | 1<<11 | 1<<6)            
            {
            //           
            // | 1 1 | | |
            // | | | 2 | |
            // 3 | | | 4 |
            // | | | | | |                        
            D({ 2, BASE, BASE, 1, 2, X }, GuitarStandardTuning::D, D::CAGED::D)
            }
        },         
        {
            "maj:7M:#11", //ajouter :/7M ?
            //mask = (1<<4 | 1<<11 | 1<<18)            
            {
            //sound flamenco
            //           x
            // | | 1 1 | |
            // | | | | | |
            // 2 3 | | 4 |
            // | | | | | |                        
            D({ 2, 2, BASE, BASE, 2, X }, GuitarStandardTuning::G, D::CAGED::G)

            }
        },
        {
            "maj:7M:#11", //ajouter :/3?
            // mask = (1<<4 | 1<<11 | 1<<18)
            {
            //sound flamenco
            // x        
            // | | 1 1 1 1
            // | | | | | |
            // | 2 | | 3 4
            // | | | | | |                        
            D({ X, 2, BASE, BASE, 2, 2 }, GuitarStandardTuning::G, D::CAGED::G),

            //   x        
            // | | 1 | | |
            // | | | | | |
            // 2 | | 3 3 |
            // | | | | | |
            // | | | | | 4                                    
            D({ 2, X, BASE, 2, 2, 4 }, GuitarStandardTuning::D, D::CAGED::D)


            }
        },
        {
            "maj:7M:no5:#4", //ajouter :/#4?
            // mask = (1<<4 | 1<<6 | 1<<11)                        
            {
            //sound flamenco
            // x         x
            // | | | 1 1 |
            // | | | | | |
            // | | | | | |
            // | | | | | |            
            // | 3 4 | | | 
            D({ X, 4, 4, BASE, BASE, X }, GuitarStandardTuning::G, D::CAGED::G) // CAGED::G & E

            }
        },
        {
            "sus2:7M:13",
            // mask = (1<<2 | 1<<11 | 1<<21)            
            {
            // x     
            // | 1 1 1 1 1
            // | | | 2 | |
            // | | 3 | | 4            
            // | | | | | |
            D({ X, BASE, 2, 1, BASE, 2 }, GuitarStandardTuning::A, D::CAGED::A) 

            }
        },
        {            
            "maj:7M:6:9",
            // mask = (1<<4 | 1<<7 | 1<<9 | 1<<11 | 1<<14)            
            {
            // | 1 1 1 1 1
            // 2 | | | 3 |
            // | | | | | |            
            D({ 1, BASE, BASE, BASE, 1, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G) 
            }                
        },
        {            
            "maj:7M:9:13:no5",
            // mask = (1<<4 | 1<<11 | 1<<14 | 1<<21)            
            {
            // 1 1 1 1 1 1
            // 2 | | | | |            
            // | | 3 | | |            
            // | | | | 4 |                        
            D({ 1, BASE, 2, BASE, 3, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G), //&CAGED:E 
            // 1 | | | | |            
            // | | 2 3 | |            
            // | | | | 4 4            
            // | | | | | |            
            D({BASE, X, 1, 1, 2, 2 }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            //   x     
            // | | | | 1 1
            // | | | | | |
            // | | | 2 | |
            // 3 | | | | |
            // | | 4 | | |
            D({ 3, X, 4, 2, 1, 1 }, GuitarStandardTuning::LOW_E, D::CAGED::E) //& CAGED::G
            }                
        },
        {
            "maj:7M:6:9:no5",
            // mask = (1<<4 | 1<<9 | 1<<11 | 1<<14)            
            {  
            // x
            // | | 1 1 1 1            
            // | | | | | |            
            // | | | 3 | |            
            // | 4 | | | |            
            D({X, 3, BASE, 2, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::C) 
            }                
        },

        { 
            "maj:7M:b5", 
            // mask = (1<<4 | 1<<11 | 1<<6)                        
            {
            //   x       x 
            // | | | | 1 | 
            // 2 | | | | | 
            // | | 3 4 | | 

            D({ 1, X, 2, 2, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::E),
            // x x 
            // | | 1 | | | 
            // | | | 2 | | 
            // | | | | 3 4 
            // | | | | | |         
            D({ X, X, BASE, 1, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D),

            }
        }
    };

    return db;
}

} // namespace chord::database

            // "",
            // {
            // // | | | | | |            
            // // | | | | | |            
            // // | | | | | |            
            // // | | | | | |            
            // D({BASE, BASE, BASE, BASE, BASE, BASE }, GuitarStandardTuning::, D::CAGED::) 
            // }                
