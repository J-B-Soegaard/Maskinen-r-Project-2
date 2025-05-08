cmake_minimum_required(VERSION 3.30)
project(Project2 C)

set(CMAKE_C_STANDARD 17)

add_definitions(-DSDL_MAIN_HANDLED)

# RIGTIGE stier til SDL2 og SDL2_ttf
include_directories(
        "C:\\Libraries\\SDL2-2.32.6\\x86_64-w64-mingw32\\include\\SDL2"
        "C:\\Libraries\\SDL2_ttf-2.24.0\\x86_64-w64-mingw32\\include\\SDL2"
)

link_directories(
        "C:\\Libraries\\SDL2-2.32.6\\x86_64-w64-mingw32\\lib"
        "C:\\Libraries\\SDL2_ttf-2.24.0\\x86_64-w64-mingw32\\lib"
)

add_executable(Project2 main.c commands.c GUI.c)

target_link_libraries(Project2 SDL2 SDL2main SDL2_ttf)