project(MySuperJavaJar VERSION 1.0.0 DESCRIPTION "CMake Java example")
add_jar(MySuperJavaJar SOURCES "TopLevelWindow.java" "NativeMethods.java" ENTRY_POINT "TopLevelWindow") 

message("Configuring java...")