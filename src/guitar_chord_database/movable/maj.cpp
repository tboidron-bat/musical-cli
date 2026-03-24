#include <musical/guitar_chord_database/movable/maj.h>

namespace chord::database
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        {
            TRIAD_MAJ,
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

        // ========================================================
        // DOMINANT 7
        // ========================================================
        {
            (TRIAD_MAJ | (1ULL << 10)),
            {
                // | 1 1 1 1 1 
                // | | | | | |
                // | | 2 | 4 |
                // | | | | | |
                D({ X, BASE, 2, BASE, 2, BASE }, GuitarStandardTuning::A, D::CAGED::A)
            }
        },

        // ========================================================
        // MAJ7 #11 (Lydien)
        // ========================================================
        {
            (TRIAD_MAJ | (1ULL << 11) | (1ULL << 6)),
            {
                //maj:7M:#4                
                //           x
                // 1 1 1 1 1 |
                // | 2 3 4 | |
                // | | | | | |
                // | | | | | |
                D({ BASE, 1, 1, 1, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::E),

                //maj:7M:#4:/5                          
                // 1 1 | | | 1
                // | | 2 3 | |
                // | | | | 4 |
                // | | | | | |
                D({ BASE, BASE, 2, 3, 4, BASE }, GuitarStandardTuning::A, D::CAGED::A),

                //maj:7M:#4:/5                
                // x          
                // | | | | 1 1
                // | | | | | |
                // | | | 2 | |
                // | 3 4 | | |
                D({ X, 3, 3, 2, BASE, BASE }, GuitarStandardTuning::D, D::CAGED::E),

                //maj:7M:#4:/3                
                // | 1 1 | | |
                // | | | 2 | |
                // 3 | | | 4 |
                // | | | | | |
                D({ 2, BASE, BASE, 1, 2, X }, GuitarStandardTuning::D, D::CAGED::D)
            }
        },

        // ========================================================
        // MAJ 6/9/13
        // ========================================================
        {
            (TRIAD_MAJ | (1ULL << 9) | (1ULL << 11) | (1ULL << 14)),
            {
                //maj:7M:6:9            
                // | 1 1 1 1 1
                // 2 | | | 3 |
                // | | | | | |
                D({ 1, BASE, BASE, BASE, 1, BASE }, GuitarStandardTuning::LOW_E, D::CAGED::G),

                // x
                // | | 1 1 1 1            
                // | | | | | |            
                // | | | 3 | |            
                // | 4 | | | |            
                D({ X, 3, BASE, 2, BASE, BASE }, GuitarStandardTuning::A, D::CAGED::C)
            }
        },
        {
            (TRIAD_MAJ_NO5 | (1ULL << 9) | (1ULL << 11) | (1ULL << 14)),            
                //maj:7M:6:9:no5            
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
            (TRIAD_MAJ_NO5 | (1ULL<<6) | (1ULL<<11)),                        
            {
            //maj:7M:b5                            
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

            //maj:7M:no5:#4:/#4
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
            (TRIAD_MAJ_NO5 | (1ULL <<11) | (1ULL <<14) | (1ULL <<21)),           
            {
            //maj:7M:9:13:no5                 
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
            (TRIAD_MAJ | (1ULL <<11) | (1ULL <<18)), 
            {
            //maj:7M:#11:/7M 
            //sound flamenco
            //           x
            // | | 1 1 | |
            // | | | | | |
            // 2 3 | | 4 |
            // | | | | | |                        
            D({ 2, 2, BASE, BASE, 2, X }, GuitarStandardTuning::G, D::CAGED::G),
            //maj:7M:#11:/3"
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
        }
    };

    return db;
}

} // namespace chord::database

/* pattern
"",
 {
 // | | | | | |            
 // | | | | | |            
 // | | | | | |            
 // | | | | | |            
 D({BASE, BASE, BASE, BASE, BASE, BASE }, GuitarStandardTuning::, D::CAGED::) 
 }                
*/