#include <musical/chord_db/movable/altered/maj7_b5.h>

namespace chord::db
{

using movable_diagram_map =
std::unordered_map<IntervalMask, std::vector<Diagram>>;

const movable_diagram_map& maj7_b5_movable()
{
    using D = Diagram;

    constexpr uint8_t BASE = 0;
    constexpr uint8_t X = D::MUTE;

    static const movable_diagram_map db =
    {
        {
            // ========================================================
            // ▲7ᵇ5
            // ========================================================
            (MAJ7_B5),          
            {            
            // x
            // | | | | | 1
            // | 2 | | | |
            // | | 3 3 | |
            // | | | | 4 |
            // | | | | | |
            // 
            D({ X, 1, 2, 2, 3, BASE }, GuitarStandardTuning::A, D::CAGED::A),

            // Sound flamenco.
            // Renversement /3M.                             
            // x         x
            // | | | 1 | |
            // | | | | | |
            // | 2 | | 3 |
            // | | | | | |            
            // | | 4 | | |
            //  3M ▲ T b5
            D({ X, 2, 4, BASE, 2, X }, GuitarStandardTuning::G, D::CAGED::G), // et un petit peu de CAGED::E

            // Sound flamenco.
            // Renversement /b5.
            // x         x
            // | | | 1 1 |
            // | | | | | |
            // | | | | | |
            // | | | | | |            
            // | 3 4 | | |
            //  5b ▲ T 3M   
            D({ X, 4, 4, BASE, BASE, X }, GuitarStandardTuning::G, D::CAGED::G), // CAGED::G & E

            //   x       x 
            // | | | | 1 | 
            // 2 | | | | | 
            // | | 3 4 | | 
            D({ 1, X, 2, 2, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::E),

            //         x x
            // 1 1 1 1 | |
            // | 2 3 4 | |
            // | | | | | |
            // | | | | | |
            // T   ▲ 3M 
            //   b5   
            D({ BASE, 1, 1, 1, BASE, X }, GuitarStandardTuning::LOW_E, D::CAGED::E),

            // Renversement : /5b                
            // x          
            // | | | | 1 1
            // | | | | | |
            // | 3 | 2 | |
            // | | 4 | | |
            // 
            D({ X, 2, 3, 2, BASE, BASE }, GuitarStandardTuning::D, D::CAGED::E),

            // x x 
            // | | 1 | | | 
            // | | | 2 | | 
            // | | | | 3 4 
            // | | | | | |         
            D({ X, X, BASE, 1, 2, 2 }, GuitarStandardTuning::D, D::CAGED::D),

            // Renversement : /3M
            //   x       x
            // | | 1 | | |
            // | | | 2 | |
            // 3 | | | 4 |
            // | | | | | |
            D({ 2, X, BASE, 1, 2, X }, GuitarStandardTuning::D, D::CAGED::D)
            }
        },
        {
            // ========================================================
            // ▲#11
            // ========================================================

            (MAJ7_SHARP11),
            {         
            // Sound flamenco.
            // Renversement /▲.
            //           x
            // | | 1 1 | |
            // | | | | | |
            // 2 3 | | 4 |
            // | | | | | |    
            // ▲ 3M  T 
            //      5  #11                    
            D({ 2, 2, BASE, BASE, 2, X }, GuitarStandardTuning::G, D::CAGED::G),

            // Sound flamenco.
            // Renversement /3M.
            // x        
            // | | 1 1 | |
            // | | | | | |
            // | 2 | | 3 4
            // | | | | | |      
            //  3M 5 T   ▲
            //        #11                  
            D({ X, 2, BASE, BASE, 2, 2 }, GuitarStandardTuning::G, D::CAGED::G),

            // Renversement /3M.
            //   x        
            // | | 1 | | |
            // | | | | | |
            // 2 | | 3 3 |
            // | | | | | |
            // | | | | | 4     
            //3M   T 5 ▲ #11                              
            D({ 2, X, BASE, 2, 2, 4 }, GuitarStandardTuning::D, D::CAGED::D)



            }
        }
    };

    return db;
}

} // namespace chord::db