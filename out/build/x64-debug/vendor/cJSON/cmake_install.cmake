# Install script for directory: C:/Users/josdd/repos/p/CVFS/vendor/cJSON

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/include/cjson/cJSON.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/include/cjson" TYPE FILE FILES "C:/Users/josdd/repos/p/CVFS/vendor/cJSON/cJSON.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/pkgconfig/libcjson.pc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/pkgconfig" TYPE FILE FILES "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/libcjson.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cjson.lib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/cjson.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/bin/cjson.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/bin" TYPE SHARED_LIBRARY FILES "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/bin/cjson.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson.cmake"
         "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/CMakeFiles/Export/C_/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON" TYPE FILE FILES "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/CMakeFiles/Export/C_/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson-debug.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON" TYPE FILE FILES "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/CMakeFiles/Export/C_/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cjson-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cJSONConfig.cmake;C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON/cJSONConfigVersion.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/josdd/repos/p/CVFS/out/install/x64-debug/lib/cmake/cJSON" TYPE FILE FILES
    "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/cJSONConfig.cmake"
    "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/cJSONConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/tests/cmake_install.cmake")
  include("C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/fuzzing/cmake_install.cmake")

endif()

