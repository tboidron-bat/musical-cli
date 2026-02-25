add_executable(test_note test_note.cpp)
target_link_libraries(test_note PRIVATE musical-core)
add_test(NAME musical_note COMMAND test_note)

add_executable(test_chord_lexer test_chord_lexer.cpp)
target_link_libraries(test_chord_lexer PRIVATE musical-core)
add_test(NAME musical_chord_lexer COMMAND test_chord_lexer)