#pragma once

#include <variant>
#include <string>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

NODE_NAMESPACE_BEGIN
class Port
{
private:
    std::variant<double, int, bool, std::string, cv::Mat> _data;

public:
    enum PortDataType
    {
        Float,
        Int,
        Bool,
        String,
        Image,
    };
    Port(const std::string &node_id, const std::string &name, PortDataType type)
        : node_id(node_id), name(name), type(type)
    {
    }
    ~Port()
    {
    }

    template <typename T>
    void set_value(T value)
    {
        this->_data = value;
    }
    template <typename T>
    T get_value()
    {
        return std::get<T>(this->_data);
    }

    std::string node_id;
    std::string name;
    PortDataType type;
};

NODE_NAMESPACE_END