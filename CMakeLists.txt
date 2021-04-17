cmake_minimum_required(VERSION 3.16)

project(ChessTree)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Tree)

target_include_directories(${PROJECT_NAME} PUBLIC Tree)

target_link_directories(${PROJECT_NAME} PRIVATE Tree)

target_link_libraries(${PROJECT_NAME} PUBLIC tree)



