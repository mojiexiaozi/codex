SET(PROJECT_NAME test)
project(${PROJECT_NAME} VERSION 0.0.1)

FILE(GLOB_RECURSE SRCS *.cpp)

include_directories(${THIRDPARTY_DIR}/include)
include_directories(${ROOT}/include)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${OpenCV})

add_subdirectory(test_node)
IF(CMAKE_SYSTEM_NAME MATCHES Linux)
target_link_libraries(${PROJECT_NAME} dl)
ELSE()
ENDIF()