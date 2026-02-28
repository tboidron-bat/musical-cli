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

        src/instruments/guitar/Tuning.cpp
        
        src/instruments/guitar/six_strings/OpenChordDiagram.cpp
        src/instruments/guitar/six_strings/MovableShapeDiagram.cpp        

        src/instruments/guitar/six_strings/database_open_a.cpp 
        src/instruments/guitar/six_strings/database_open_c.cpp
        src/instruments/guitar/six_strings/database_open_d.cpp
        src/instruments/guitar/six_strings/database_open_e.cpp
        src/instruments/guitar/six_strings/database_open_g.cpp
        src/instruments/guitar/six_strings/db_open_queries.cpp
        
        
        src/instruments/guitar/six_strings/database_movable_a.cpp         
        src/instruments/guitar/six_strings/db_movable_queries.cpp

        src/io/utils/input/normalize_to_ascii.cpp                

        src/io/note/input/NoteLexer.cpp                
        src/io/note/input/NoteParser.cpp        
        src/io/note/output/note_formatter.cpp
        src/io/note/output/stream.cpp                
        src/io/note/output/mei_adapter.cpp        

        src/io/chord/output/stream.cpp                
        src/io/chord/input/ChordLexer.cpp          
        src/io/chord/input/ChordParser.cpp              
        src/io/chord/output/formatter.cpp
                
        src/io/scale/scalepattern_formatter.cpp

        src/io/instruments/guitar/six_strings/open_chord_diagram_to_ascii.cpp    
        src/io/instruments/guitar/six_strings/movable_chord_diagram_to_ascii.cpp    

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
