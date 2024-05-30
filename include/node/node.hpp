#pragma once

#include <utility>

#include "utils/utils.hpp"
#include "utils.hpp"
#include "property.hpp"

NODE_NAMESPACE_BEGIN
class Node
{
public:
    enum State
    {
        NORMAL,
        RUNNING,
        FINISHED,
        STATE_ERROR
    };
    nlohmann::json dumps()
    {
        nlohmann::json cfg;
        std::vector<nlohmann::json> props;
        props.reserve(property_map_.size());
        for (auto &&p : property_map_)
        {
            props.push_back(p.second->dumps());
        }
        cfg["node_type"] = Node::node_type;
        cfg["name"] = Node::name;

        cfg["user_name"] = this->user_name_;
        cfg["id"] = this->id_;
        cfg["property"] = props;
        return cfg;
    }

    virtual ~Node() = default;

    void run()
    {
        if (this->executed())
        {
            return;
        }
        try
        {

            this->init();
            this->on_start();
            this->execute();
            this->on_finished();
        }
        catch (const std::exception &e)
        {
            spdlog::error(e.what());
            this->on_error();
        }
    }
    void reset()
    {
        std::lock_guard<std::mutex> lock(this->mutex_);
        this->state = NORMAL;
    }
    [[nodiscard]] bool executed() const
    {
        return FINISHED == this->state || STATE_ERROR == this->state;
    }
    void rename(std::string user_name)
    {
        this->user_name_ = std::move(user_name);
    }
    [[nodiscard]] std::string get_name() const
    {
        return this->user_name_;
    }
    [[nodiscard]] uint get_id() const
    {
        return this->id_;
    }

    bool add_property(const uint &id,
                      const std::string &name,
                      Property::PropertyType property_type,
                      Property::PropertyDataType data_type)
    {
        std::lock_guard<std::mutex> lock(this->mutex_);
        if (utils::find(this->property_map_, id))
        {
            spdlog::warn("add property failed, id exits: ", id);
            return false;
        }

        auto prop = create_property(id, name, property_type, data_type);
        if (prop != nullptr)
        {
            this->property_map_[id] = prop;
            return true;
        }
        return false;
    }
    bool add_property(const std::string &name,
                      Property::PropertyType property_type,
                      Property::PropertyDataType data_type)
    {
        return this->add_property(this->gen_index(), name, property_type, data_type);
    }
    bool add_property(nlohmann::json cfg)
    {
        std::lock_guard<std::mutex> lock(this->mutex_);
        uint id = cfg["id"];
        if (utils::find(this->property_map_, id))
        {
            spdlog::warn("add property failed, id exits: ", id);
            return false;
        }

        auto prop = create_property(cfg);
        if (prop != nullptr)
        {
            this->property_map_[id] = prop;
            return true;
        }
        return false;
    }
    State state{NORMAL};
    static std::string name;
    static std::string node_type;

protected:
    Node(std::string user_name, uint id) : user_name_(std::move(user_name)), id_(id)
    {
    }
    explicit Node(const nlohmann::json &cfg)
    {
        this->id_ = cfg["id"];
        this->user_name_ = cfg["user_name"];
        for (const auto& p : cfg["property"])
        {
            this->add_property(p);
        }
    }
    virtual void init() = 0;
    virtual void unit() = 0;
    virtual void execute() = 0;

    virtual void on_start()
    {
        this->state = RUNNING;
    }
    virtual void on_finished()
    {
        this->state = FINISHED;
    }
    virtual void on_error()
    {
        this->state = STATE_ERROR;
    }
    uint gen_index()
    {
        for (uint i = 0; i < 1000; i++)
        {
            if (!utils::find(this->property_map_, i))
            {
                return i;
            }
        }
        return this->property_map_.size() + 1;
    }

    std::map<uint, Property *> property_map_;
    uint id_{0};
    std::string user_name_;
    std::mutex mutex_;
    bool initialized_{false};
};
NODE_NAMESPACE_END
