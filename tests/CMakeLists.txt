add_executable(tests
    test_Game.cpp
)

target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src/class
    ${PROJECT_SOURCE_DIR}/src/utils
)

target_link_libraries(tests
    gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(tests)