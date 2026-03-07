cmake_minimum_required(VERSION 3.16)

project(musical-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# mscale
# =========================
add_executable(mscale
    src/scale/scale_cmd.cpp
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
    src/command_option.cpp
    src/chord/diagram_layout.cpp        
    src/chord/ChordCommand.cpp    
    src/chord/help_option.cpp    
    src/chord/diagram_option.cpp
    src/chord/difficulty_option.cpp
    src/chord/dumpdb_option.cpp
    src/chord/play_option.cpp
    src/chord/random_option.cpp                
    src/chord/tuning_option.cpp                        
)

target_link_libraries(chord
    PRIVATE musical-core
)

target_include_directories(chord
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS chord mscale DESTINATION bin)
