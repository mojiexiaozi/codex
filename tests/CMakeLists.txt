SET(PROJECT_NAME test)
project(${PROJECT_NAME} VERSION 0.0.1)

FILE(GLOB_RECURSE SRCS *.cpp)

include_directories(${THIRDPARTY_DIR}/include)
include_directories(${ROOT}/include)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${OpenCV})