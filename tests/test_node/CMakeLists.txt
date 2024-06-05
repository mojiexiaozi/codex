SET(PROJECT_NAME test_node${BUILD_FLAG})
project(${PROJECT_NAME} VERSION 0.0.1)

FILE(GLOB_RECURSE SRCS *.cpp)
foreach(file ${SRCS})
    message(${file})
endforeach()

# 为Debug和Release配置分别设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ROOT}/build/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT}/build/bin/lib)
# 为Debug和Release配置分别设置库文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${ROOT}/build/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${ROOT}/build/bin/lib)
add_library(${PROJECT_NAME} SHARED ${SRCS})
target_link_libraries(${PROJECT_NAME} ${OpenCV})