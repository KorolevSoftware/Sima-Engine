cmake_minimum_required(VERSION 3.14)
project(Sima-Engine C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ----------------------------- DEPENDENCY BRGIN-----------------------------
include(FetchContent)

FetchContent_Declare(sokoltools
 GIT_REPOSITORY https://github.com/KorolevSoftware/sokol-tools-bin-only-cmake.git
 GIT_TAG 5df9ad5553533ac520b7edd3587569e1bb35e546
)

FetchContent_Declare(physfs
 GIT_REPOSITORY https://github.com/icculus/physfs
 GIT_TAG 957176bcf1db005e2528242636f644d9121013d5
)


# SDL3 OPTIONS

SET(SDL_SHARED OFF)
FetchContent_Declare(SDL3
 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
 GIT_TAG release-2.28.3
)

FetchContent_MakeAvailable(sokoltools )

set(DEP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependency)

set(SOKOL_HEADERS ${DEP_PATH}/sokol) # Sokol graphic backend
add_subdirectory(${DEP_PATH}/Forth-embed)

# ----------------------------- DEPENDENCY END-----------------------------




include(${sokoltools_SOURCE_DIR}/sokol_shader_utils.cmake)
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mesh.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/render.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/render.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/sprite.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sprite.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/script.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/script.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/game_object.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/game_object.h

    ${CMAKE_CURRENT_SOURCE_DIR}/dependency/cmath/mathc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/dependency/cmath/mathc.c

    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/texture.h

    ${CMAKE_CURRENT_SOURCE_DIR}/include/STDImage.h
   
 main.c)

sokol_shader(triangle-sapp.glsl hlsl5)

add_executable(${PROJECT_NAME} ${SOURCES} triangle-sapp.glsl.h)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOKOL_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${SDL2_INCLUDE_DIR}
    ${MATH_HEADERS}
    # physfs-static 
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # SDL2::SDL2
    Forth-embed
    # PhysFS::PhysFS-static
)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    # -WX
  )
endif()