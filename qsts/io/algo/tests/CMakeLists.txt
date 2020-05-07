add_executable(convert_test convert_test.cpp)
target_link_libraries(convert_test
                      gtest_main
)

add_test(NAME convert_test COMMAND convert_test)
