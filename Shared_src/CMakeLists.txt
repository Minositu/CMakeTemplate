Project(CMakeSharedLibrary LANGUAGES CXX DESCRIPTION "CMake example.")
add_library(MySuperSharedLibrary SHARED "main.cpp" "main.h")

message("Configuring Shared Library")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MySuperSharedLibrary PROPERTY CXX_STANDARD 20)
endif()