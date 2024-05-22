#include <iostream>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "node/property.hpp"
#include "node/node.hpp"
#include "node/utils.hpp"
#include "utils/dll_helper.hpp"
#include <iostream>

int main()
{
    auto image_path = "/workspaces/codex/assets/0.png";
    auto img = cv::imread(image_path, cv::IMREAD_COLOR);
    std::cout << image_path << std::endl;
    spdlog::info("welcome to spdlog");
    spdlog::error("goodby");

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

    node::Node *test_node;
    const char *file = "/workspaces/codex/build/tests/test_node/build/lib/libtest_noded.so";
    auto ok = utils::call_func(file, node::NAME_OF_CREATE_NODE, test_node, std::string("test_node"), 1);
    if (ok)
    {
        test_node->init();
        test_node->execute();
        test_node->uninit();
        std::cout << test_node->dumps() << std::endl;
    }

    node::Node *cfg_node;
    auto cfg = test_node->dumps();
    ok = utils::call_func(file, node::NAME_OF_CREATE_NODE_CFG, cfg_node, cfg);
    if (ok)
    {
        cfg_node->init();
        cfg_node->execute();
        cfg_node->uninit();
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