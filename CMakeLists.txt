cmake_minimum_required(VERSION 2.6)
project(Azo)

set(PROJECT_ENGINE_DIR "engine")
set(PROJECT_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(ENGINE_INCLUDE_DIR "engine/include")
set(PROJECT_INCLUDE_DIR "include/")
set(PROJECT_ASSETS_DIR "assets/")
set(COMPILE_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS} -std=c++0x")

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
  set(GENERAL_IMAGES_DIR "assets/general_images")
  set(INSTALLER_DESCRIPTION_FILE "../INSTALLER_DESCRIPTION.txt")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Instalador para o jogo Azo. O jogo será instalado no diretório /usr/local/AzoGame. Para a execução do jogo, é necessário que o sistema possua o SDL instalado. Visite www.libsdl.org para mais informações. O projeto Azo é um projeto de código aberto. Visite https://github.com/TheAzoTeam/Azo para mais informações sobre o jogo e sobre como adquirir o código fonte.")
  set(CPACK_PACKAGE_FILE_NAME "Azo_Installer")
  set(CPACK_PACKAGE_NAME "Azo")

  install(TARGETS Azo RUNTIME DESTINATION AzoGame/)
  install(DIRECTORY ${AUDIOS_DIR} DESTINATION AzoGame/)
  install(DIRECTORY ${SPRITES_DIR} DESTINATION AzoGame/)
  install(DIRECTORY ${BACKGROUNDS_DIR} DESTINATION AzoGame/)
  install(DIRECTORY ${GENERAL_IMAGES_DIR} DESTINATION AzoGame/)
endif(UNIX)
  include(CPack)