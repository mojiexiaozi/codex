cmake_minimum_required(VERSION 3.5) # cmake最低版本

SET(PROJECT_NAME codex)
project(${PROJECT_NAME} VERSION 0.0.1)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
# SET(CMAKE_AUTOUIC ON)
# SET(CMAKE_AUTOMOC ON)
# SET(CMAKE_AUTORCC ON)

# 默认编译debug
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

# 编译产物标志
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(BUILD_FLAG d)
ELSE()
    SET(BUILD_FLAG "")
ENDIF()

# 编译路径
set(ROOT ${PROJECT_SOURCE_DIR})

# 为Debug和Release配置分别设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/bin)
# 为Debug和Release配置分别设置库文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/lib)

# 三方库
SET(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/3rdparty)
SET(OpenCV_DIR ${THIRDPARTY_DIR}/opencv)
SET(GoogleTest_DIR ${THIRDPARTY_DIR}/googletest)

IF(CMAKE_SYSTEM_NAME MATCHES Linux)
    FILE(GLOB_RECURSE OpenCV ${OpenCV_DIR}/lib/${CMAKE_BUILD_TYPE}/*.so*)
    FILE(GLOB_RECURSE OpenCV_Bin ${OpenCV})
    FILE(GLOB_RECURSE GoogleTest ${GoogleTest_DIR}/lib/${CMAKE_BUILD_TYPE}/*.a)
ELSE()
    FILE(GLOB_RECURSE OpenCV ${OpenCV_DIR}/lib/${CMAKE_BUILD_TYPE}/*.lib)
    FILE(GLOB_RECURSE OpenCV_Bin ${OpenCV_DIR}/lib/${CMAKE_BUILD_TYPE}/*.dll)
    FILE(GLOB_RECURSE GoogleTest ${GoogleTest_DIR}/lib/${CMAKE_BUILD_TYPE}/*.lib)
ENDIF()

# foreach(file  ${OpenCV})
#     message(${file})
# endforeach()
# foreach(file  ${OpenCV_Bin})
#     message(${file})
# endforeach()
# foreach(file  ${GoogleTest})
#     message(${file})
# endforeach()

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)