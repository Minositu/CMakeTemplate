project(MySuperJavaJar VERSION 1.0.0 DESCRIPTION "CMake Java example")
add_jar(MySuperJavaJar SOURCES "TopLevelWindow.java" "NativeMethods.java" ENTRY_POINT "TopLevelWindow" OUTPUT_DIR "${CMAKE_BINARY_DIR}/../../../build/${PRESET}") 

message("Configuring java...")