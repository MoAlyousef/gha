cmake_minimum_required(VERSION 3.15)
project(embed_gtk)
set(FLTK_BUILD_TEST OFF CACHE BOOL " " FORCE)
include(FetchContent)

FetchContent_Declare( 
  FLTK
  GIT_REPOSITORY https://github.com/FLTK/FLTK
  GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(FLTK)

add_executable(main main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(main fltk X11 ${GTK3_LIBRARIES})

