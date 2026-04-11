cmake_minimum_required(VERSION 3.16)

project(musical-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# mscale
# =========================
add_executable(mscale
    src/command/scale/scale_cmd.cpp
)

target_link_libraries(mscale
    PRIVATE musical-core
)

target_include_directories(mscale
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# =========================
# chord
# =========================
add_executable(chord
    src/main.cpp
    src/Option.cpp
    src/option_parameter_t.cpp
    src/command/chord/diagram_layout.cpp        
    src/command/chord/ChordCommand.cpp    
    src/command/chord/version_option.cpp    
    src/command/chord/help_option.cpp    
    src/command/chord/diagram_option.cpp
    src/command/chord/difficulty_option.cpp
    src/command/chord/dumpdb.cpp
    src/command/chord/play_option.cpp
    src/command/chord/random_option.cpp                
    src/command/chord/tuning_option.cpp         
    
    src/command/chord/chord_parser.cpp            
)

target_link_libraries(chord
    PRIVATE musical-core
    asound
)

target_include_directories(chord
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS chord mscale DESTINATION bin)
