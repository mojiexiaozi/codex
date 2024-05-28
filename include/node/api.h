#pragma once

#include <nlohmann/json.hpp>
#include "node.hpp"

EXPORT_BEGIN
node::Node *create_node(const std::string &name, uint id);
node::Node *create_node_from_cfg(const nlohmann::json &cfg);
std::string get_node_name()
{
    return node::Node::name;
}
std::string get_node_type()
{
    return node::Node::node_type;
}
EXPORT_END