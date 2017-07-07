cmake_minimum_required(VERSION 2.6)
project(Azo)

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


if(WIN32)
  set(CPACK_GENERATOR "NSIS")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Roger Lenke")
  set(CPACK_PACKAGE_FILE_NAME "Azo")


  set(AUDIOS_DIR "assets/audios")
  set(SPRITES_DIR "assets/sprites")
  set(BACKGROUNDS_DIR "assets/backgrounds")
  set(INSTALLATION_DIR "/home/rdlenke/AzoGame")

  install(TARGETS Azo RUNTIME DESTINATION AzoGame)
  install(DIRECTORY ${AUDIOS_DIR} DESTINATION AzoGame)
  install(DIRECTORY ${SPRITES_DIR} DESTINATION AzoGame)
  install(DIRECTORY ${BACKGROUNDS_DIR} DESTINATION AzoGame)
endif(WIN32)
if(UNIX)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_SOURCE_GENERATOR "TGZ")

  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Roger Lenke")
  set(CPACK_SET_DESTDIR ON)

  set(AUDIOS_DIR "assets/audios")
  set(SPRITES_DIR "assets/sprites")
  set(BACKGROUNDS_DIR "assets/backgrounds")

  install(TARGETS Azo RUNTIME DESTINATION /home/rdlenke/AzoGame/)
  install(DIRECTORY ${AUDIOS_DIR} DESTINATION /home/rdlenke/AzoGame/)
  install(DIRECTORY ${SPRITES_DIR} DESTINATION /home/rdlenke/AzoGame/)
  install(DIRECTORY ${BACKGROUNDS_DIR} DESTINATION /home/rdlenke/AzoGame/)
endif(UNIX)
  include(CPack)