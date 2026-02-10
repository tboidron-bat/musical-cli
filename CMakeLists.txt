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
        src/Core/note/Note.cpp
        src/Core/note/NoteFactory.cpp
        src/Core/note/NoteService.cpp

        src/Core/chord/Chord.cpp
        src/Core/chord/ChordFactory.cpp
        src/Core/chord/guitar/chord_guitar_diagram.cpp
        src/Core/chord/guitar/chord_guitar_diagram_db_6.cpp        
        src/Core/chord/guitar/chord_guitar_diagram_ascii_6.cpp

        src/Core/Arpeggio.cpp
        src/Core/Cadence.cpp

        src/Core/Figure.cpp
        src/Core/ScaleKeyed.cpp
        src/Core/ScaleKeyedFactory.cpp
        src/Core/GuitarTuning.cpp
        # src/Core/Mode.cpp   # désactivé pour l'instant        
        src/Core/Rest.cpp
        src/Core/ScalePattern.cpp
        src/Core/ScalePatternFactory.cpp

        src/IO/chord/chord_lexer.cpp                
        src/IO/chord/chord_grammar.cpp
        src/IO/chord/chord_formatter.cpp
        src/IO/chord/chord_parser.cpp
        src/IO/scale/scalepattern_formatter.cpp

        # Analysis
        src/Analysis/ChordAnalysis.cpp
        src/Analysis/ChordFunctionAnalyser.cpp
        src/Analysis/chord_name.cpp
        src/Analysis/Harmonizer.cpp
        # src/Analysis/Harmony.cpp # désactivé pour l'instant        


        # ScoreElements
        src/ScoreElements/KeySignature.cpp
        src/ScoreElements/Measure.cpp
        src/ScoreElements/TimeSignature.cpp
)

target_include_directories(musical-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()
add_subdirectory(tests)
