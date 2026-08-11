cmake_minimum_required(VERSION 4.1)
project(Chip8)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_subdirectory(libs/SDL-release-3.4.14 EXCLUDE_FROM_ALL)

add_executable(Chip8 main.cpp
        Hardware/memory.cpp
        Hardware/cpu.cpp
        Hardware/keyboard.cpp
        Hardware/display.cpp
        Renderer/window.cpp
        Renderer/window.h
        Renderer/renderer.cpp
        Renderer/renderer.h
        Renderer/texture.cpp
        Renderer/texture.h
        Renderer/input.cpp
        Renderer/input.h
)

target_link_libraries(Chip8 PRIVATE SDL3::SDL3)
