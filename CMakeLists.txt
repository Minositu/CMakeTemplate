﻿cmake_minimum_required (VERSION 3.8)

# Main Project
project(main LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "CMake example.")

# MSVC Runtime config
if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()

if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory("Shared_src")
add_subdirectory("Static_src")
add_subdirectory("Executable_src")

# Include directories for each project 
target_include_directories(MySuperExecutable PUBLIC "Executable_src/include")

# Platform dependant libraries
if(LINUX)
  message("Current OS is LINUX")
  set(CMAKE_CXX_FLAGS "-DPLATFORM_LINUX")
  target_link_libraries( MySuperSharedLibrary "-lxcb" )
elseif(WIN32)
  message("Current OS is WIN32")
  set(CMAKE_CXX_FLAGS "-DPLATFORM_WIN32")
endif()