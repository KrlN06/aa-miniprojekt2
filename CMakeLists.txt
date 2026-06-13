cmake_minimum_required(VERSION 3.20)
project(Projekt2_Nalepa_Petelicki LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Projekt2_Nalepa_Petelicki
    src/main.cpp
    src/attack/AttackDetector.cpp
    src/board/Board.cpp
    src/engine/Engine.cpp
    src/engine/Evaluation.cpp
    src/engine/MoveGenerator.cpp
    src/pieces/PieceMovement.cpp
    src/rules/GameRules.cpp
    src/utils/BitboardUtils.cpp
    src/validation/MoveValidator.cpp
    include/attack/AttackDetector.h
    include/board/Board.h
    include/board/Square.h
    include/engine/Engine.h
    include/engine/Evaluation.h
    include/engine/MoveGenerator.h
    include/move/Move.h
    include/pieces/PieceMovement.h
    include/pieces/Pieces.h
    include/rules/GameRules.h
    include/utils/BitboardUtils.h
    include/validation/MoveValidator.h
)

target_include_directories(Projekt2_Nalepa_Petelicki PRIVATE include)
