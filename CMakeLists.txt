cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(feodorov-translation-lab3 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_COMPILER_IS_GNUCC)
    message(STATUS "Detected GNU compiler. Using specific flags.")
    set(CMAKE_C_FLAGS_DEBUG "-pipe -Wall -Wextra -Wpedantic -O0 -ggdb")
    set(CMAKE_C_FLAGS_RELEASE "-pipe -march=native -O3")
endif()

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)


add_subdirectory(src)


enable_testing()

add_subdirectory(tests)
