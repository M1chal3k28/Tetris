cmake_minimum_required(VERSION 3.27.2)
project(Tetris VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/thirdparty)

add_executable(Tetris main.cpp)
target_link_libraries(${PROJECT_NAME} raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
