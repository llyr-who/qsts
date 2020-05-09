add_executable(graph_test graph_test.cpp)
target_link_libraries(graph_test
                      gtest_main
)
add_test(NAME graph_test COMMAND graph_test)

add_executable(infix_test infix_test.cpp)
target_link_libraries(infix_test
                      gtest_main
)
add_test(NAME infix_test COMMAND infix_test)

add_executable(token_test token_test.cpp)
target_link_libraries(token_test
                      gtest_main
)
add_test(NAME token_test COMMAND token_test)

