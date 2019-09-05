cmake_minimum_required(VERSION 2.8)

project(Sudoku)


# Download and unpack memoized-member at configure time
configure_file(CMakeLists.memoized-member.in memoized-member-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -DCMAKE_INSTALL_PREFIX=../memoized-member-install .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/memoized-member-download)
if(result)
  message(FATAL_ERROR "CMake step for MemoizedMember failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/memoized-member-download)
if(result)
  message(FATAL_ERROR "Build step for MemoizedMember failed: ${result}")
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/memoized-member-install/cmake/MM.cmake)


# Download and unpack power-iterator at configure time
configure_file(CMakeLists.power-iterator.in power-iterator-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -DCMAKE_INSTALL_PREFIX=../power-iterator-install .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/power-iterator-download)
if(result)
  message(FATAL_ERROR "CMake step for MemoizedMember failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/power-iterator-download)
if(result)
  message(FATAL_ERROR "Build step for MemoizedMember failed: ${result}")
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/power-iterator-install/cmake/PowerIterators.cmake)


add_subdirectory(src/Sudoku)
add_subdirectory(test)

