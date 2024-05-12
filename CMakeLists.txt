cmake_minimum_required(VERSION 3.27.2)
project(Tetris VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/thirdparty)

set(SOURCE_FILES
    src/Grid.cpp
    src/Block.cpp
    src/Position.cpp
    src/Blocks.cpp
    src/Colors.cpp
    src/Game.cpp
    src/Timer.cpp
)

add_executable(Tetris main.cpp ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
