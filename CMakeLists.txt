cmake_minimum_required(VERSION 3.20)
project(Projekt2_Nalepa_Petelicki LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Projekt2_Nalepa_Petelicki
    src/main.cpp
    src/board/Board.cpp
    src/utils/BitboardUtils.cpp
    include/board/Board.h
    include/board/Square.h
    include/move/Move.h
    include/pieces/Pieces.h
    include/utils/BitboardUtils.h
        src/validation/MoveValidator.cpp
    include/validation/MoveValidator.h
        src/attack/AttackDetector.cpp
        include/attack/AttackDetector.h
        include/pieces/PieceMovement.h
        src/pieces/PieceMovement.cpp
        src/rules/GameRules.cpp
        include/rules/GameRules.h
)

target_include_directories(Projekt2_Nalepa_Petelicki PRIVATE include)
