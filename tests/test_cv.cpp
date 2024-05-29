#include <iostream>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "node/property.hpp"
#include "node/node.hpp"
#include "node/utils.hpp"
#include "node/node_manager.hpp"
#include "utils/dll_helper.hpp"
#include <iostream>

int main()
{
    auto image_path = "/workspaces/codex/assets/0.png";
    auto img = cv::imread(image_path, cv::IMREAD_COLOR);
    std::cout << image_path << std::endl;
    spdlog::info("welcome to syslog");
    spdlog::error("goodly");

    node::StringProperty str_property(1, "1", node::Property::NORMAL);
    str_property.set_value(std::string("hi"));
    spdlog::info(str_property.get_value<std::string>());
    std::cout << str_property.dumps() << std::endl;

    node::FloatProperty f_property(2, "2", node::Property::NORMAL);
    f_property.set_value(0.1111);
    spdlog::info(f_property.get_value<double>());
    std::cout << f_property.dumps() << std::endl;

    node::FloatProperty f_property1(f_property.dumps());
    std::cout << f_property.dumps() << std::endl;

    node::ImageProperty im_property(3, "3", node::Property::NORMAL);
    im_property.set_value(img);
    std::cout << im_property.dumps() << std::endl;
    cv::imwrite("test.png", im_property.get_value<cv::Mat>());

    std::string path = "lib";
    node::NodeLibManager manager(path);
    for (auto &&i : manager.get_lib_names())
    {
        spdlog::info("{},{}", i.first, i.second[0]);
    }

    auto test_node = manager.create_node(std::string("start"), std::string("test_node"), 1);
    manager.create_node(std::string("start"), std::string("test_node1"), 1);
    if (test_node)
    {
        test_node->run();
        std::cout << test_node->dumps() << std::endl;
    }

    auto cfg_node = manager.create_node(test_node->dumps());
    if (test_node)
    {
        cfg_node->run();
        std::cout << cfg_node->dumps() << std::endl;
    }

    std::vector<int> v = {1, 2, 3, 4};
    auto i = utils::find(v, 2);
    spdlog::info(i);
    spdlog::info(utils::find_if(v, [](int n)
                                { return n % 2 == 0; }));

    spdlog::info(v[i]);
    spdlog::info(v[-1]);

    for (auto &&i : utils::get_if(v, [](int n)
                                  { return n % 2 == 0; }))
    {
        spdlog::info(i);
    }

    std::vector<int> res;
    utils::copy_if(v, res, [](int n)
                   { return n % 2 == 0; });
    for (auto &&i : res)
    {
        spdlog::info(i);
    }

    return 0;
}