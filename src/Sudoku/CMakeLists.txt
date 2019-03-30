set (HEADERS
  Cell.hpp
  Grid.hpp
  Puzzle.hpp
  Size.hpp
  Slice.hpp
  SliceType.hpp
  Solver.hpp
)

set (SOURCES
  Cell.cpp
  Grid.cpp
  Slice.cpp
  Solver.cpp
)

add_library (sudoku ${SOURCES} ${HEADERS})
