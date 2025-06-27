cmake_minimum_required(VERSION 3.10)
project(LinkListContact C)

# 使用 C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 自动收集源码文件
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

# 默认输出文件名（可被外部覆盖）
set(APP_NAME "LinkListContact" CACHE STRING "App name")

# 输出到 bin 目录（相对于 build 目录）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# 生成目标
add_executable(${APP_NAME} ${SRC_FILES})

# 打印平台信息（用于调试）
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
