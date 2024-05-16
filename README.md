# codex
自动化检测通用框架

https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html
cmake \
 -DBUILD_TESTS=OFF \
 -DBUILD_PERF_TESTS=OFF \
 -DBUILD_EXAMPLES=OFF \
 -DBUILD_opencv_apps=OFF \
 -DBUILD_opencv_world=ON \
 -CMAKE_BUILD_TYPE=Release \
 -DCMAKE_INSTALL_PREFIX=../install \
  ../opencv-4.9.0

make -j8