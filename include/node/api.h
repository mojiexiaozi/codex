#pragma once

#include "utils/utils.hpp"
#include "node.hpp"

EXPORT node::Node *create_node(const std::string &name, uint id);
EXPORT node::Node *create_node_from_cfg(const nlohmann::json &cfg);
EXPORT const char* get_node_name()
{
    return node::Node::name.c_str();
}
EXPORT const char* get_node_type()
{
    return node::Node::node_type.c_str();
}
