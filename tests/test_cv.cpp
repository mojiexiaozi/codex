#include <iostream>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "node/port.hpp"
#include <iostream>

int main()
{
    auto image_path = "/workspaces/codex/assets/0.png";
    auto img = cv::imread(image_path, cv::IMREAD_COLOR);
    std::cout << image_path << std::endl;
    spdlog::info("welcome to spdlog");
    spdlog::error("goodby");

    node::Port port("1", "2", node::Port::PortDataType::String);
    port.set_value(std::string("hi"));
    spdlog::info(port.get_value<std::string>());

    node::Port port1("1", "2", node::Port::PortDataType::Image);
    port1.set_value(img);

    cv::imwrite("test.png", port1.get_value<cv::Mat>());
    return 0;
}