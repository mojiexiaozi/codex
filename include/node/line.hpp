#pragma once

#include "utils.hpp"
#include "utils/utils.hpp"

NODE_NAMESPACE_BEGIN
class Line
{
public:
    Line(uint node1_id, uint node2_id) : node1_id_(node1_id), node2_id_(node2_id) {}
    ~Line() = default;
    uint get_other_node_id(uint node_id)
    {
        if (node_id == node1_id_)
        {
            return node2_id_;
        }
        else if (node_id == node2_id_)
        {
            return node1_id_;
        }
        else
        {
            return -1;
        }
    }

private:
    uint node1_id_;
    uint node2_id_;
};
NODE_NAMESPACE_END