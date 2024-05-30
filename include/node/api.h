#pragma once

#include "utils/utils.hpp"
#include "node.hpp"

EXPORT node::Node *create_node(const std::string &name, uint id);
EXPORT node::Node *create_node_from_cfg(const nlohmann::json &cfg);
EXPORT const char* get_node_name()
{
    return node::Node::name.c_str();
//    // 动态分配内存，长度为字符串长度加1（用于终止符 '\0'）
//    char* name = new char[node::Node::name.length() + 1];
//
//    // 使用 std::strcpy 复制字符串内容
//    std::strcpy(name, node::Node::name.c_str());
//
//    return name;
}

EXPORT const char* get_node_type()
{
    return node::Node::node_type.c_str();
//// 动态分配内存，长度为字符串长度加1（用于终止符 '\0'）
//    char* node_type = new char[node::Node::node_type.length() + 1];
//
//    // 使用 std::strcpy 复制字符串内容
//    std::strcpy(node_type, node::Node::node_type.c_str());
//
//    return node_type;
}
