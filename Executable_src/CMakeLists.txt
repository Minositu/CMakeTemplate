project(MySuperExecutable)
add_executable(MySuperExecutable "main.cpp")

message("Configuring executable")

# Project dependencies
target_link_libraries(MySuperExecutable PRIVATE MySuperSharedLibrary)
target_link_libraries(MySuperExecutable PRIVATE MySuperStaticLibrary)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MySuperExecutable PROPERTY CXX_STANDARD 20)
endif()