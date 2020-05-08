add_executable(graph_test graph_test.cpp)
target_link_libraries(graph_test
                      gtest_main
)

add_test(NAME graph_test COMMAND graph_test)

