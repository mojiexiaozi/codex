#pragma once

#include "utils.hpp"
#include "utils/utils.hpp"

NODE_NAMESPACE_BEGIN
class Property
{
public:
    enum PropertyDataType
    {
        Float,
        Int,
        Bool,
        String,
        Image,
    };
    enum PropertyType
    {
        NORMAL,
        RUNNING,
        OUTPUT,
    };
    virtual ~Property() {}

    virtual nlohmann::json dumps()
    {
        nlohmann::json cfg;
        cfg["id"] = this->id_;
        cfg["name"] = this->name_;
        cfg["property_type"] = this->property_type_;
        cfg["data_type"] = this->data_type_;
        return cfg;
    }

    // TODO: 类型校验
    template <typename T>
    void set_value(T value)
    {
        this->data_ = value;
    }
    // TODO: 类型校验
    template <typename T>
    T get_value()
    {
        return std::get<T>(this->data_);
    }

protected:
    Property(const uint& id, const std::string& name, PropertyType property_type)
        : id_(id), name_(name), property_type_(property_type)
    {
    }
    Property(nlohmann::json cfg) : Property(cfg["id"], cfg["name"], cfg["property_type"]) {}
    std::variant<double, float, int, bool, std::string, cv::Mat> data_;
    uint id_;
    std::string name_;
    PropertyDataType data_type_;
    PropertyType property_type_;
};

class FloatProperty : public Property
{
public:
    FloatProperty(const uint& id, const std::string& name, PropertyType property_type)
        : Property(id, name, property_type)
    {
        this->data_type_ = Float;
        this->set_value<double>(0.0);
    }
    FloatProperty(nlohmann::json cfg) : FloatProperty(cfg["id"], cfg["name"], cfg["property_type"])
    {
        this->set_value<double>(cfg["value"]);
    }
    nlohmann::json dumps() override
    {
        auto cfg = Property::dumps();
        cfg["value"] = this->get_value<double>();
        return cfg;
    }
};

class IntProperty : public Property
{
public:
    IntProperty(const uint& id, const std::string& name, PropertyType property_type) : Property(id, name, property_type)
    {
        this->data_type_ = Int;
        this->set_value(0);
    }
    IntProperty(nlohmann::json cfg) : IntProperty(cfg["id"], cfg["name"], cfg["property_type"])
    {
        this->set_value<int>(cfg["value"]);
    }
    nlohmann::json dumps() override
    {
        auto cfg = Property::dumps();
        cfg["value"] = this->get_value<int>();
        return cfg;
    }
};

class BoolProperty : public Property
{
public:
    BoolProperty(const uint& id, const std::string& name, PropertyType property_type)
        : Property(id, name, property_type)
    {
        this->data_type_ = Bool;
        this->set_value(false);
    }
    BoolProperty(nlohmann::json cfg) : BoolProperty(cfg["id"], cfg["name"], cfg["property_type"])
    {
        this->set_value<bool>(cfg["value"]);
    }
    nlohmann::json dumps() override
    {
        auto cfg = Property::dumps();
        cfg["value"] = this->get_value<bool>();
        return cfg;
    }
};

class StringProperty : public Property
{
public:
    StringProperty(const uint& id, const std::string& name, PropertyType property_type)
        : Property(id, name, property_type)
    {
        this->data_type_ = String;
        this->set_value<std::string>(std::string(""));
    }
    StringProperty(nlohmann::json cfg) : StringProperty(cfg["id"], cfg["name"], cfg["property_type"])
    {
        this->set_value<std::string>(cfg["value"]);
    }
    nlohmann::json dumps() override
    {
        auto cfg = Property::dumps();
        cfg["value"] = this->get_value<std::string>();
        return cfg;
    }
};

class ImageProperty : public Property
{
public:
    ImageProperty(const uint& id, const std::string& name, PropertyType property_type)
        : Property(id, name, property_type)
    {
        this->data_type_ = Image;
        this->data_ = 0.0;
    }
    ImageProperty(nlohmann::json cfg) : ImageProperty(cfg["id"], cfg["name"], cfg["property_type"]) {}
    nlohmann::json dumps() override
    {
        auto cfg = Property::dumps();
        return cfg;
    }
};

inline Property* create_property(const uint& id, const std::string& name, Property::PropertyType property_type,
                                 Property::PropertyDataType data_type)
{
    switch (data_type)
    {
        case Property::Float:
            return new FloatProperty(id, name, property_type);
        case Property::Int:
            return new IntProperty(id, name, property_type);
        case Property::Bool:
            return new BoolProperty(id, name, property_type);
        case Property::String:
            return new StringProperty(id, name, property_type);
        case Property::Image:
            return new ImageProperty(id, name, property_type);
        default:
            spdlog::warn("create property failed.");
            return nullptr;
    }
}

inline Property* create_property(nlohmann::json cfg)
{
    Property::PropertyDataType data_type = cfg["data_type"];
    switch (data_type)
    {
        case Property::Float:
            return new FloatProperty(cfg);
        case Property::Int:
            return new IntProperty(cfg);
        case Property::Bool:
            return new BoolProperty(cfg);
        case Property::String:
            return new StringProperty(cfg);
        case Property::Image:
            return new ImageProperty(cfg);
        default:
            spdlog::warn("create property failed.");
            return nullptr;
    }
}

NODE_NAMESPACE_END