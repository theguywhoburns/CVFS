# CMake generated Testfile for 
# Source directory: C:/Users/josdd/repos/p/CVFS/vendor/cJSON
# Build directory: C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "C:/Users/josdd/repos/p/CVFS/out/build/x64-debug/vendor/cJSON/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/josdd/repos/p/CVFS/vendor/cJSON/CMakeLists.txt;248;add_test;C:/Users/josdd/repos/p/CVFS/vendor/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
