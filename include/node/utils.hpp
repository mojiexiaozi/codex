#pragma once

#ifndef NODE_NAMESPACE_BEGIN
#define NODE_NAMESPACE_BEGIN \
    namespace node           \
    {
#define NODE_NAMESPACE_END }
#endif

NODE_NAMESPACE_BEGIN
const char *const NAME_OF_CREATE_NODE = "create_node";
const char *const NAME_OF_CREATE_NODE_CFG = "create_node_from_cfg";
const char *const NAME_OF_GET_NODE_NAME = "get_node_name";
const char *const NAME_OF_GET_NODE_TYPE = "get_node_type";
NODE_NAMESPACE_END