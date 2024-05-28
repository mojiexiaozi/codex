# 查找Qt包
# find_package(Qt6 COMPONENTS Widgets REQUIRED)

FILE(GLOB_RECURSE SRCS *.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
# 链接QT库
# target_link_libraries(MyQtProject PRIVATE Qt6::Widgets)