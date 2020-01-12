project(main)

include_directories(../gtest ../gtest/include)

set(SRC candy.cpp)

add_executable(exam ${SRC})
target_link_libraries(exam gtest)
