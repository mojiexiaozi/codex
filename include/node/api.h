#pragma once

#include <nlohmann/json.hpp>
#include "node.hpp"

EXPORT_BEGIN
node::Node *create_node(std::string name, uint id);
node::Node *create_node_from_cfg(nlohmann::json cfg);
const std::string &get_node_name()
{
    return node::Node::name;
}
const std::string &get_node_type()
{
    return node::Node::node_type;
}
EXPORT_END