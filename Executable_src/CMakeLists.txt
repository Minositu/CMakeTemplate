project(MySuperExecutable)
add_executable(MySuperExecutable "main.cpp")

message("Configuring executable")

# Project dependencies
add_dependencies(MySuperExecutable MySuperStaticLibrary)
target_link_libraries(MySuperExecutable MySuperStaticLibrary)
target_link_libraries(MySuperExecutable MySuperSharedLibrary)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MySuperExecutable PROPERTY CXX_STANDARD 20)
endif()