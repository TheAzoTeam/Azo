set(ENGINE_INCLUDE_DIR "include/" CACHE INTERNAL "")
include_directories(${ENGINE_INCLUDE_DIR})
file(GLOB SOURCES "src/*.cpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
add_library(SDL2_Engine STATIC ${SOURCES})











