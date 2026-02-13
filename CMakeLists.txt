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
        # src/Core/Mode.cpp   # désactivé pour l'instant        



        src/Core/note/Note.cpp
        src/Core/note/Factory.cpp

        src/Core/note/Rest.cpp        

        src/Core/chord/Chord.cpp
        src/Core/chord/Factory.cpp
        src/Core/chord/Arpeggio.cpp        

        src/Core/scale/ScaleKeyed.cpp
        src/Core/scale/ScaleKeyedFactory.cpp
        src/Core/scale/ScalePattern.cpp
        src/Core/scale/ScalePatternFactory.cpp

        src/instruments/guitar/Tuning.cpp
        
        src/instruments/guitar/chord_guitar_diagram.cpp
        src/instruments/guitar/chord_guitar_diagram_db_6.cpp        
        src/instruments/guitar/chord_guitar_diagram_ascii_6.cpp

        src/io/note/stream.cpp        
        src/io/note/input/Lexer.cpp                
        src/io/note/input/Parser.cpp        
        src/io/note/note_formatter.cpp
        src/io/note/mei_adapter.cpp        

        src/io/chord/lexer.cpp          
        src/io/chord/parser.cpp              
        src/io/chord/formatter.cpp        
        src/io/scale/scalepattern_formatter.cpp

        # analysis
        src/analysis/ChordAnalysis.cpp
        src/analysis/ChordFunctionAnalyser.cpp
        src/analysis/chord_name.cpp
        src/analysis/Harmonizer.cpp
        # src/analysis/Harmony.cpp # désactivé pour l'instant        


        # ScoreElements
        src/ScoreElements/KeySignature.cpp
        src/ScoreElements/Measure.cpp
        src/ScoreElements/TimeSignature.cpp
)

target_include_directories(musical-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(cli)
enable_testing()
add_subdirectory(tests)
