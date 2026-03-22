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

        src/Core/Cadence.cpp
        src/Core/Figure.cpp
        src/Core/pitch_t.cpp        
        # src/Core/Mode.cpp   # désactivé pour l'instant        

        src/Core/note/Note.cpp
        src/Core/note/Factory.cpp

        src/Core/note/Rest.cpp        

        src/Core/chord/ChordType.cpp        
        src/Core/chord/ChordTypeCatalog.cpp                
        src/Core/chord/Chord.cpp
        src/Core/chord/Factory.cpp
        src/Core/chord/Arpeggio.cpp        

        src/Core/scale/ScaleKeyed.cpp
        src/Core/scale/ScaleKeyedFactory.cpp
        src/Core/scale/ScalePattern.cpp
        src/Core/scale/ScalePatternFactory.cpp

        # ScoreElements
        src/ScoreElements/KeySignature.cpp
        src/ScoreElements/Measure.cpp
        src/ScoreElements/TimeSignature.cpp


        src/guitar_chord_database/Tuning.cpp

        src/guitar_chord_database/Diagram.cpp        
        src/guitar_chord_database/data_open.cpp 
        src/guitar_chord_database/open_queries.cpp
        src/guitar_chord_database/data_movable.cpp         
        src/guitar_chord_database/movable_queries.cpp

        # guitar chord diagram        
        src/io/guitar/unicode/GridCore.cpp                 
        src/io/guitar/unicode/OpenGrid.cpp                  
        src/io/guitar/unicode/DottedGrid.cpp                                  
        src/io/guitar/unicode/DiagramRenderer.cpp                                                

        #src/io/guitar/unicode/MovableDiagram.cpp                                

        


        src/io/utils/in/normalize_to_ascii.cpp                

        src/io/note/in/NoteLexer.cpp                
        src/io/note/in/NoteParser.cpp        
        src/io/note/out/note_formatter.cpp
        src/io/note/out/stream.cpp                
        src/io/note/out/mei_adapter.cpp        

        src/io/chord/out/stream.cpp                
        src/io/chord/in/ChordLexer.cpp          
        src/io/chord/in/ChordParser.cpp        
        src/io/chord/out/formatter.cpp
                
        src/io/scale/scalepattern_formatter.cpp


        # analysis
        src/analysis/ChordAnalysis.cpp
        src/analysis/ChordFunctionAnalyser.cpp
        src/analysis/chord/naming.cpp
        #src/analysis/Harmonizer.cpp
        # src/analysis/Harmony.cpp # désactivé pour l'instant        


        src/audio/wave/chord_player.cpp
        src/audio/karplus_strong/chord_player.cpp        
)

target_include_directories(musical-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(cli)
enable_testing()
add_subdirectory(tests)
