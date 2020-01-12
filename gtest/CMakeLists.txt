project(gtest)

include_directories(./ include)

set(SRC 
    src/gtest-all.cc
    src/gtest_main.cc)

add_library(gtest ${SRC})
