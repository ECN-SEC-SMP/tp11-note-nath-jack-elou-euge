cmake_minimum_required(VERSION 3.15)

# Project name and version
set(PROJECT_NAME "SMP-TP11")
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(SRC_DIR "./src")
set(CLASS_DIR "./src/class")
set(UTILS_DIR "./src/utils")


# Set C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_NAME} ${CLASS_DIR})
include_directories(${PROJECT_NAME} ${UTILS_DIR})

# Add your source files
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${CLASS_DIR}/TermCtrl.cpp
    ${CLASS_DIR}/Board.cpp
    ${CLASS_DIR}/Case.cpp
    ${CLASS_DIR}/Display.cpp
    ${CLASS_DIR}/Game.cpp
    ${CLASS_DIR}/Player.cpp
    ${CLASS_DIR}/Robot.cpp
    ${CLASS_DIR}/Target.cpp
    ${UTILS_DIR}/Timer.cpp
    ${UTILS_DIR}/Utils.cpp

)

add_executable(${PROJECT_NAME}.bin ${SOURCES})

target_link_libraries(${PROJECT_NAME}.bin PRIVATE pthread)

# Add a message to indicate success
message(STATUS "Compilation succeed")