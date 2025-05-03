cmake_minimum_required(VERSION 3.30)
project(Project2 C)

set(CMAKE_C_STANDARD 17)

add_executable(Project2
        main.c
        commands.c
        game_display.c
        # Tilføj flere .c filer her
)
