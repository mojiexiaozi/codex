#include "node.hpp"
#include "utils.hpp"

NODE_NAMESPACE_BEGIN
class NodeLibManager
{
public:
    explicit NodeLibManager(const std::string& lib_path)
    {
        std::vector<std::string> libs;
        utils::get_files(lib_path, SUFFIX, libs);

        for (std::string lib : libs)
        {
            try
            {
                const char* node_name;
                const char* node_type;
                auto res1 = this->lib_manager_.call_func(lib, NAME_OF_GET_NODE_NAME, node_name);
                auto res2 = this->lib_manager_.call_func(lib, NAME_OF_GET_NODE_TYPE, node_type);
                if (!res1 || !res2)
                {
                    spdlog::warn("get node name or node type failed: {}", lib);
                    continue;
                }
                auto node_type_str = std::string(node_type);
                auto node_name_str = std::string(node_name);
                spdlog::info("get node type, node name : {},{}", node_type_str, node_name_str);
                this->node_libs_[node_type_str][node_name_str] = lib;
            }
            catch (const std::exception& e)
            {
                spdlog::error(e.what());
            }
        }
    }
    Node* create_node(const std::string& node_type, const std::string& node_name, uint node_id)
    {
        Node* node{nullptr};
        if (!utils::find(this->node_libs_, node_type) || !utils::find(this->node_libs_[node_type], node_name))
        {
            spdlog::warn("not found: {},{}", node_type, node_name);
            return node;
        }
        auto lib = this->node_libs_[node_type][node_name];
        this->lib_manager_.call_func(lib, node::NAME_OF_CREATE_NODE, node, node_name + std::to_string(node_id),
                                     node_id);
        return node;
    }
    Node* create_node(const nlohmann::json& cfg)
    {
        Node* node{nullptr};
        std::string node_type = cfg["node_type"];
        std::string node_name = cfg["name"];
        if (!utils::find(this->node_libs_, node_type) || !utils::find(this->node_libs_[node_type], node_name))
        {
            spdlog::warn("not found: {},{}", node_type, node_name);
            return node;
        }
        auto lib = this->node_libs_[node_type][node_name];
        this->lib_manager_.call_func(lib, node::NAME_OF_CREATE_NODE_CFG, node, cfg);
        return node;
    }
    std::map<std::string, std::vector<std::string>> get_lib_names()
    {
        std::map<std::string, std::vector<std::string>> lib_names;
        for (auto&& i : this->node_libs_)
        {
            std::map<std::string, std::string> libs = i.second;
            lib_names[i.first] = std::vector<std::string>();
            for (auto&& lib : libs)
            {
                lib_names[i.first].push_back(lib.first);
            }
        }

        return lib_names;
    }
    ~NodeLibManager() {}

private:
    std::map<std::string, std::map<std::string, std::string>> node_libs_;
    utils::DynamicLibManager lib_manager_;
};
NODE_NAMESPACE_END