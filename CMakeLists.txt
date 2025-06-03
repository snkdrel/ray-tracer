cmake_minimum_required(VERSION 3.10)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_library(tuples src/tuples.cpp)
add_library(canvas src/canvas.cpp)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PUBLIC tuples)
target_link_libraries(tests PUBLIC canvas)

project(ray-tracer)

add_executable(ray-tracer src/main.cpp)