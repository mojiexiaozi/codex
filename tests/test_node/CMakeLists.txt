SET(PROJECT_NAME test_node${BUILD_FLAG})
project(${PROJECT_NAME} VERSION 0.0.1)

FILE(GLOB_RECURSE SRCS *.cpp)
foreach(file ${SRCS})
    message(${file})
endforeach()


add_library(${PROJECT_NAME} SHARED ${SRCS})