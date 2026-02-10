add_executable(test_note test_note.cpp)
target_link_libraries(test_note PRIVATE musical-core)

add_test(NAME musical_note COMMAND test_note)
