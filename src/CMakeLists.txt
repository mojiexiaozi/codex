# 查找Qt包
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${THIRDPARTY_DIR}/include)
include_directories(${ROOT}/include)

FILE(GLOB_RECURSE SRCS *.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
# 链接QT库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
