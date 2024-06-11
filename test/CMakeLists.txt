cmake_minimum_required(VERSION 3.0)  # cmake -G "MinGW Makefiles" ..
project(BLACK_TEST VERSION 1.0)

# gtest库相关
# 如果把gtest放到test目录下，则使用如下包含关系：
include_directories(../googletest-main)  # 编译gtest
include_directories(../googletest-main/googletest/include)  # 包含gtest等头文件
include_directories(../googletest-main/googlemock/include)  # 包含gmock等头文件
# include_directories(../googletest/lib) 

# 设置编译选项以启用 gcov
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")


add_subdirectory(../src src)
# 头文件目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../src/")
# 源文件目录
# AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/../../src/" SRCS)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 测试代码目录
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}" TEST_SRCS)

# 生成测试可执行程序
add_executable(black_test ${TEST_SRCS})

find_library(gtest libgtest.a ../googletest-main/lib)
find_library(gtest_main libgtest_main.a ../googletest-main/lib)
find_library(gmock libgmock.a ../googletest-main/lib)
find_library(gmock_main libgmock_main.a ../googletest-main/lib)
# 链接测试库,pthread 库一定要写在 ${GTEST_BOTH_LIBRARIES} 的后面, 否则编译时会报错,
# GTEST_BOTH_LIBRARIES表示链接google test的两个库
target_link_libraries(black_test
        PRIVATE 
        ${gtest}
        ${gtest_main}  # 使用gtest带的main函数,如果检测到外部有main函数，则使用外部main函数,外部main函数要配置gtest初始化。
        ${gmock}
        ${gmock_main} # 使用gmock带的main函数,如果检测到外部有main函数，则使用外部main函数,与gtest_main同时存在则自动配置。
        pthread 
        MyLibrary
        )

# 添加测试
enable_testing()
# 添加测试
add_test(NAME MyProgramTest COMMAND black_test)