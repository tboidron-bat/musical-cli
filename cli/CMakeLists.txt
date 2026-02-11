cmake_minimum_required(VERSION 3.16)

# Le projet CLI vit DANS musical-core
project(musical-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- binaire mscale ----
add_executable(mscale
    commands/scale_cmd.cpp
    output/text.cpp
)

target_link_libraries(mscale
    PRIVATE musical-core
)

# ---- binaire chord ----
add_executable(chord
    commands/chord_cmd.cpp
    output/text.cpp
)

target_link_libraries(chord
    PRIVATE musical-core
)

install(TARGETS chord mscale DESTINATION bin)
