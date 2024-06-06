#pragma once
#include "utils/dll_helper.hpp"
#include "utils/utils.hpp"

#ifndef NODE_NAMESPACE_BEGIN
#define NODE_NAMESPACE_BEGIN \
    namespace node           \
    {
#define NODE_NAMESPACE_END }
#endif

#ifdef OS_WINDOWS
#define SUFFIX ".dll"
#elif defined(OS_LINUX)
#define SUFFIX ".so"
#else
// TODO: 其它系统
#endif

NODE_NAMESPACE_BEGIN
static std::string NAME_OF_CREATE_NODE = "create_node";
static std::string NAME_OF_CREATE_NODE_CFG = "create_node_from_cfg";
static std::string NAME_OF_GET_NODE_NAME = "get_node_name";
static std::string NAME_OF_GET_NODE_TYPE = "get_node_type";
NODE_NAMESPACE_END