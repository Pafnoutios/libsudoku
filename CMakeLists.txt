###
###	@file      sudokupuzzle.h
###	@author    John Szwast
###	@date      2013
###


set (HEADERS src/sudokucell.h src/sudokupuzzle.h src/sudokuslice.h)
set (SOURCES src/sudokucell.cpp src/sudokupuzzle.cpp src/sudokuslice.cpp)

add_library (sudoku ${SOURCES} ${HEADERS})
