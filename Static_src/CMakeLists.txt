Project(MySuperStaticLibrary LANGUAGES C VERSION 1.0.0 DESCRIPTION "CMake example.")
add_library(MySuperStaticLibrary "dothing.c")

message("Configuring static library")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MySuperStaticLibrary PROPERTY CXX_STANDARD 20)
endif()