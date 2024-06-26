cmake_minimum_required (VERSION 3.8)

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fdiagnostics-color=always -fansi-escape-codes)
    endif ()
endif ()

# Android error handling
if(NOT DEFINED ENV{ANDROID_NDK_ROOT} AND ANDROID)
  message(FATAL_ERROR "Please define the environment variable ANDROID_NDK_ROOT.")
endif()

# Main Project
project(main LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "CMake example.")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../../build/${PRESET}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../../build/${PRESET}")
set (CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../../build/${PRESET}")

# Policy configs
if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()

# MSVC Specific config
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory("Shared_src")
add_subdirectory("Static_src")
add_subdirectory("Executable_src")

if (NOT ANDROID)
  find_package(Java REQUIRED)
  find_package(JNI REQUIRED)  # Disable this if you're not using the java native interface.
  
  message("${JAVA_INCLUDE_PATH}")
  include(UseJava)
  target_include_directories(MySuperStaticLibrary PUBLIC "${JNI_INCLUDE_DIRS}")
  add_subdirectory("Java_src")
endif()
# Include directories for each project 
target_include_directories(MySuperExecutable PUBLIC "Executable_src/include")

# Platform dependant config, definitions and libraries
if(ANDROID)
  message("Current OS is ${CMAKE_SYSTEM_NAME}")
  target_compile_definitions(MySuperSharedLibrary PUBLIC PLATFORM_ANDROID)
  target_compile_definitions(MySuperStaticLibrary PUBLIC PLATFORM_ANDROID)
elseif(LINUX)
  message("Current OS is ${CMAKE_SYSTEM_NAME}")
  target_compile_definitions(MySuperSharedLibrary PUBLIC PLATFORM_LINUX)
elseif(WIN32)
  message("Current OS is ${CMAKE_SYSTEM_NAME}")
  target_compile_definitions( MySuperSharedLibrary PUBLIC EXPORT_API)
  target_compile_definitions(MySuperSharedLibrary PUBLIC PLATFORM_WIN32)

endif()