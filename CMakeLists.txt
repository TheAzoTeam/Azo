cmake_minimum_required(VERSION 2.6)
project(game)

set(PROJECT_ENGINE_DIR "engine")
set(PROJECT_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(ENGINE_INCLUDE_DIR "engine/include")
set(PROJECT_INCLUDE_DIR "include/")
set(PROJECT_ASSETS_DIR "assets/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(${PROJECT_ENGINE_DIR})
include_directories(${ENGINE_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR})
file(GLOB SOURCES "${PROJECT_SRC_DIR}/*.cpp")
file(COPY ${PROJECT_ASSETS_DIR} DESTINATION ${CMAKE_BINARY_DIR})                      
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2_Engine 
                      SDL2 SDL2_image SDL2_ttf SDL2_mixer)
