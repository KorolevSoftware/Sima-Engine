cmake_minimum_required(VERSION 3.14)
project(Sima-Engine C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ----------------------------- DEPENDENCY BRGIN-----------------------------
include(FetchContent)

FetchContent_Declare(sokol
 GIT_REPOSITORY https://github.com/floooh/sokol.git
 GIT_TAG d4ac122f36d7659a18b312fd4fa2317fb9e06a63
)

FetchContent_Declare(sokoltools
 GIT_REPOSITORY https://github.com/KorolevSoftware/sokol-tools-bin-only-cmake.git
 GIT_TAG 5df9ad5553533ac520b7edd3587569e1bb35e546
)

FetchContent_Declare(physfs
 GIT_REPOSITORY https://github.com/icculus/physfs
 GIT_TAG 957176bcf1db005e2528242636f644d9121013d5
)


# SDL3 OPTIONS

# SET(SDL_SHARED OFF)
FetchContent_Declare(SDL3
 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
 GIT_TAG release-2.28.3
)

FetchContent_MakeAvailable(sokol physfs sokoltools SDL3)

# ----------------------------- DEPENDENCY END-----------------------------



include(${sokoltools_SOURCE_DIR}/sokol_shader_utils.cmake)
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mesh.h
 main.c)

sokol_shader(triangle-sapp.glsl hlsl5)

add_executable(${PROJECT_NAME} ${SOURCES} triangle-sapp.glsl.h)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${sokol_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIR}
    # physfs-static 

)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2 
    PhysFS::PhysFS-static
)