cmake_minimum_required(VERSION 3.22)

project(CVFS VERSION 0.1.0 LANGUAGES C CXX)

if(MSVC)
	add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
else()
	add_compile_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(vendor/cJSON)

file(GLOB_RECURSE CVFS_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_library(CVFS ${CVFS_SOURCES}) 
target_include_directories(CVFS PUBLIC include src vendor/cJSON)
target_link_libraries(CVFS PUBLIC cjson)
if(true)
add_executable(test test/main.c ${CVFS_SOURCES})
target_include_directories(test PUBLIC include src test vendor/cJSON)
target_link_libraries(test PUBLIC cjson)
endif()