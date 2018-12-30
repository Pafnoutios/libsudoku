set (HEADERS
  Cell.hpp
  Grid.hpp
  Size.hpp
  Slice.hpp
  SliceType.hpp
)

set (SOURCES
  Cell.cpp
  Grid.cpp
  Slice.cpp
)

add_library (sudoku ${SOURCES} ${HEADERS})
