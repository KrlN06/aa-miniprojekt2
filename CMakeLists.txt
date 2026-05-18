cmake_minimum_required(VERSION 3.20)
project(Projekt2_Nalepa_Petelicki LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Projekt2_Nalepa_Petelicki
    src/main.cpp
)

target_include_directories(Projekt2_Nalepa_Petelicki PRIVATE include)
