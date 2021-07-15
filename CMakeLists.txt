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

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${GTK3_INCLUDE_DIRS} ${fltk_SOURCE_DIR} ${fltk_BINARY_DIR} )
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(main PUBLIC fltk fltk_gl X11 ${GTK3_LIBRARIES})

