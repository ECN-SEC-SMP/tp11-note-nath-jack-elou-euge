add_executable(tests
    test_Player.cpp
    test_Board.cpp
    test_Robot.cpp
    test_Target.cpp
    test_Timer.cpp
    test_Utils.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Robot.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Player.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Board.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Case.cpp
    ${PROJECT_SOURCE_DIR}/src/class/Target.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Utils.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Timer.cpp

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
