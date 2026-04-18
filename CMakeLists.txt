cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(musical-core
    VERSION 0.1
    LANGUAGES CXX
)

add_library(musical-core STATIC)

# 👉 la lib sera générée dans modules/musical-core/
set_target_properties(musical-core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(musical-core
    PRIVATE

        #core
        src/core/Cadence.cpp
        src/core/Figure.cpp
        #src/Core/Pitch.cpp        
        # src/Core/Mode.cpp   # désactivé pour l'instant        

        src/core/note/Note.cpp
        src/core/note/NoteFactory.cpp

        src/core/note/Rest.cpp        

        #core::Chord
        src/core/chord/ChordType.cpp        
        src/core/chord/ChordTypeCatalog.cpp                
        src/core/chord/Chord.cpp
        src/core/chord/ChordFactory.cpp
        #src/Core/chord/Arpeggio.cpp        

        #core::Scale        
        src/core/scale/ScaleKeyed.cpp
        src/core/scale/ScaleKeyedFactory.cpp
        src/core/scale/ScalePattern.cpp
        src/core/scale/ScalePatternFactory.cpp

        # ScoreElements
        src/ScoreElements/KeySignature.cpp
        src/ScoreElements/Measure.cpp
        src/ScoreElements/TimeSignature.cpp

        #guitar chord database
        src/chord_db/Diagram.cpp        
        #gc_db#open
        src/chord_db/open/database.cpp 
        src/chord_db/open/queries.cpp
        src/chord_db/open/maj.cpp                 
        src/chord_db/open/min.cpp                 
        src/chord_db/open/dim.cpp                 
        src/chord_db/open/aug.cpp                 
        src/chord_db/open/sus2.cpp                 
        src/chord_db/open/sus4.cpp                 
        #gc_db#movable
        src/chord_db/movable/database.cpp         
        src/chord_db/movable/queries.cpp    
        #gc_db#movable#triads    
        src/chord_db/movable/triads/maj.cpp                             
        src/chord_db/movable/triads/min.cpp                 
        src/chord_db/movable/triads/aug.cpp                         

        src/chord_db/movable/dim.cpp                 

        src/chord_db/movable/triads/sus2.cpp                 
        src/chord_db/movable/sus4.cpp  
        #gc_db#movable#seventh
        src/chord_db/movable/sevenths/dominant7.cpp
        src/chord_db/movable/sevenths/maj7.cpp 
        src/chord_db/movable/sevenths/min7.cpp 
        src/chord_db/movable/sevenths/dominant7_sus2.cpp        
        src/chord_db/movable/sevenths/maj7_sus2.cpp                
        #gc_db#movable#altered
        src/chord_db/movable/altered/maj7_b5.cpp            
        src/chord_db/movable/altered/aug_maj7.cpp                    
        src/chord_db/movable/altered/aug_7.cpp                            


        #gc_db#movable#extensions
        src/chord_db/movable/extensions/add9.cpp             
        src/chord_db/movable/extensions/maj9.cpp             
        src/chord_db/movable/extensions/min7add11.cpp        
        src/chord_db/movable/extensions/maj13_sus2.cpp                                  

        # guitar chord diagram        
        src/io/chord_db/unicode/GridCore.cpp                 
        src/io/chord_db/unicode/OpenGrid.cpp                  
        src/io/chord_db/unicode/DottedGrid.cpp                                  
        src/io/chord_db/unicode/DiagramRenderer.cpp                                                

        #io      
        src/io/utils/in/normalize_to_ascii.cpp                
        src/io/core/note/in/NoteLexer.cpp                
        src/io/core/note/in/NoteParser.cpp        
        src/io/core/note/out/note_formatter.cpp
        src/io/core/note/out/mei_adapter.cpp        


        src/io/core/chord/parser/ChordLexer.cpp          
        src/io/core/chord/parser/ChordParser.cpp   
        src/io/core/chord/out/naming.cpp             
                
        src/io/core/scale/scalepattern_formatter.cpp


        # analysis
        src/analysis/ChordAnalysis.cpp
        src/analysis/ChordFunctionAnalyser.cpp
        #src/analysis/Harmonizer.cpp
        # src/analysis/Harmony.cpp # désactivé pour l'instant        

        # audio
        src/audio/synthesis/KarplusStrong.cpp
        src/audio/players/ChordPlayer.cpp
        src/audio/engine/AlsaEngine.cpp 
        src/audio/synthesis/basicsignalsgenerator.cpp      
)

target_include_directories(musical-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(cli)
enable_testing()
add_subdirectory(tests)
