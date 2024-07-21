cmake_minimum_required(VERSION 3.22)


project(CVFS VERSION 0.1.0 LANGUAGES C CXX)

#check Platform
if(WIN32 OR _WIN32 OR WIN64 OR _WIN64)
    # Windows-specific setup
    message(STATUS "Configuring for Windows")
    add_definitions(-DCVFS_WINDOWS)
    # Add Windows-specific definitions, include directories, or other configurations
elseif(APPLE)
    # macOS-specific setup
    message(STATUS "Configuring for macOS")
    add_definitions(-DCVFS_APPLE)
    # Add macOS-specific definitions, include directories, or other configurations
elseif(UNIX)
    # Unix-like platform (Linux, BSD, etc.) setup
    message(STATUS "Configuring for Unix-like platform")
    add_definitions(-DCVFS_UNIX)
    # Add Unix-like platform-specific definitions, include directories, or other configurations
else()
    message(WARNING "Unsupported platform")
    add_definitions(-DCVFS_UNKNOWN)
endif()

if(MSVC)
	add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
    add_definitions(/DVFS_VERSION_MAJOR=0)
    add_definitions(/DVFS_VERSION_MINOR=0)
    add_definitions(/DVFS_VERSION_PATCH=1)
    add_definitions(/DVFS_VERSION_ADDITIONAL="")
else()
	add_compile_definitions(-D_CRT_SECURE_NO_WARNINGS)
    #define VFS_VERSION "0.0.1"
    add_definitions(-DVFS_VERSION_MAJOR=0)
    add_definitions(-DVFS_VERSION_MINOR=0)
    add_definitions(-DVFS_VERSION_PATCH=1)
    add_definitions(-DVFS_VERSION_ADDITIONAL="")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vendor/cJSON)

file(GLOB_RECURSE CVFS_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_library(CVFS ${CVFS_SOURCES}) 
target_include_directories(CVFS PUBLIC include src vendor/cJSON)
target_link_libraries(CVFS PUBLIC cjson)

if(true)
add_executable(test test/main.c test/console.c ${CVFS_SOURCES})
target_include_directories(test PUBLIC include src test vendor/cJSON)
target_link_libraries(test PUBLIC cjson)

endif()