Project(CMakeSharedLibrary LANGUAGES CXX DESCRIPTION "CMake example.")
add_library(MySuperSharedLibrary SHARED "CreateWin32Window.cpp" "createLinuxWindow.cpp")

message("Configuring Shared Library")

if (LINUX)
  target_link_libraries( MySuperSharedLibrary "-lxcb" )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MySuperSharedLibrary PROPERTY CXX_STANDARD 20)
endif()