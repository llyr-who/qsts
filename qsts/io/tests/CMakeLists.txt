add_executable(expression_test expression_test.cpp)
target_link_libraries(expression_test
                      gtest_main
)

add_test(NAME expression_test COMMAND expression_test)

