#include "node/node.hpp"
#include "node/api.h"

class TestNode : public node::Node
{
public:
    TestNode(std::string name, uint id) : Node(name, id)
    {
        this->add_property(0, "float", node::Property::NORMAL, node::Property::Float);
        this->add_property(0, "float", node::Property::NORMAL, node::Property::Float);
        this->add_property("int", node::Property::NORMAL, node::Property::Int);
        this->add_property("bool", node::Property::NORMAL, node::Property::Bool);
        this->add_property("string", node::Property::RUNNING, node::Property::String);
        this->add_property("image", node::Property::OUTPUT, node::Property::Image);
    }
    TestNode(nlohmann::json cfg) : Node(cfg)
    {
    }
    virtual ~TestNode() {}
    virtual void init()
    {
        spdlog::info("init TestNode");
    }
    virtual void uninit()
    {
        spdlog::info("uninit TestNode");
    }
    virtual void execute()
    {
        spdlog::info("execute TestNode");
    }
};

const std::string node::Node::name = "test_node";
const std::string node::Node::node_type = "start";

node::Node *create_node(std::string name, uint id)
{
    return new TestNode(name, id);
}

node::Node *create_node_from_cfg(nlohmann::json cfg)
{
    return new TestNode(cfg);
}