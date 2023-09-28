cmake_minimum_required(VERSION 3.26)
project(UDP_Smart_Set2023 C)

set(CMAKE_C_STANDARD 23)

add_executable(UDP_Smart_Set2023 main.c
        server.c
        client.c)
