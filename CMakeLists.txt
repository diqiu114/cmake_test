# cmake的最低版本要求
cmake_minimum_required(VERSION 3.0)

#[[
    符号说明：
    &{}：可以解析变量
]]

# 生成vscode的库包含文件
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# 告诉cmake，版本低于3.21时，执行使用当前主要版本和次要版本的策略版本
# 高于则采用主要版本3，次要版本21的策略版本
if(${CMAKE_VERSION} VERSION_LESS 3.21)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.0)
endif()

message("${CMAKE_VERSION}")
message("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

# 检查CMake版本是否满足特定，以下表示：条件主要版本==3，次要版本要高于10
if (CMAKE_MAJOR_VERSION EQUAL 3 AND CMAKE_MINOR_VERSION GREATER_EQUAL 30)
    message("使用符合条件的CMake版本")
else()
    message("CMake版本不符合条件")
endif()

# 生成工程
project(cmake_demo)

# project(cmake_demo VERSION 1.0
#                   DESCRIPTION "Very nice project"
#                   LANGUAGES CXX)

# 生成静态库，静态库再cmake里叫
add_library(lib_demo SHARED lib_test.cc lib_test.h)

add_library(lib_demo2 SHARED lib/lib_test2.cc lib/lib_test2.h)

#[[
    这里PUBLIC和PRIVATE区别：就是这个库是否能被其他文件递归查看的问题
    比如：lib_test.h中包含了lib_test2.h，然后main只包含lib_test.h去访问
    lib_test2.h时，如果不是PUBLIC就会报错，(这里main.cc依然可以包含
    lib_test2.h，但前提是lib_test.h要
    包含lib_test2.h，因为lib_test.h连接的是lib_test2.h)
]]
target_link_libraries(lib_demo PUBLIC lib_demo2)


add_executable(demo main.cc)

target_include_directories(demo PUBLIC lib)

# 将静态库连接进执行程序
target_link_libraries(demo PRIVATE lib_demo)


set(MY_LIST "one;two")

message(${MY_LIST})


#[[
    尽管您可以在CMake中设置和获取环境变量，
    但最好只在必要时使用这些方法，并在使用
    时谨慎考虑其影响。最佳实践是尽量使用
    CMake的内置机制来管理构建过程。
]]
# 获取环境变量，这里可以获取到系统环境变量USER
message($ENV{USER})
# 设置环境变量variable_name为value
# set(ENV{variable_name} value)



set(BOOL_NUM TRUE)

if(BOOL_NUM)
    message("测试if else 值为 TRUE")
else()
    message("测试if else 值为 FALSE")
endif()


message("测试生成器")
set(value "sadf")
set(generator_expressions $<KEYWORD:value>)
message(${${generator_expressions}})

