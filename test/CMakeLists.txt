add_executable(GridTest GridTest.cpp)

target_include_directories(GridTest PRIVATE ../src)
target_link_libraries(GridTest sudoku)

add_executable(PuzzleTest PuzzleTest.cpp)

target_include_directories(PuzzleTest PRIVATE ../src)
target_link_libraries(PuzzleTest sudoku)
