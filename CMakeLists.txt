cmake_minimum_required(VERSION 3.17.2)

project(Aster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory("Test")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("Libraries/glfw")
add_subdirectory("Libraries/glm")
add_subdirectory("Libraries/glad")

add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory("Source")

target_link_libraries(Aster glfw)
target_link_libraries(Aster glm)
target_link_libraries(Aster glad)