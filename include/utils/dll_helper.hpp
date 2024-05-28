#pragma once

#include "utils.hpp"

#ifdef OS_WINDOWS
#include <windows.h>
#elif defined(OS_LINUX)
#include <dlfcn.h>
#else
// TODO: 其它系统
#endif

UTILS_NAMESPACE_BEGIN
template <typename T, typename... Args>
using FuncPtr = T (*)(Args...);

template <typename T, typename... Args>
bool call_func(const std::string &lib_name, const std::string &func_name, T& res, Args... args)
{
    FuncPtr<T, Args...> func_p;

#ifdef OS_WINDOWS
    // 打开共享库
    HMODULE handle = LoadLibraryA(lib_name.c_str());
    if (!handle)
    {
        spdlog::error("Error opening library: {}", GetLastError());
        return false;
    }
    // 获取共享库中的函数指针并调用
    func_p = (FuncPtr)GetProcAddress(handle, func_name.c_str());
    if (!func_p)
    {
        spdlog::error("Error getting symbol: {}", GetLastError());
        FreeLibrary(handle);
        return false;
    }

    // 调用共享库中的函数
    res = func_p(args...);

    // 关闭共享库
    FreeLibrary(handle);
    return true;
#elif defined(OS_LINUX)
    // 打开共享库
    void *handle = dlopen(lib_name.c_str(), RTLD_LAZY);
    if (!handle)
    {
        spdlog::error("Error opening library: {}", dlerror());
        return false;
    }

    // 获取共享库中的函数指针并调用
    func_p = reinterpret_cast<FuncPtr<T, Args...>>(dlsym(handle, func_name.c_str()));
    if (!func_p)
    {
        spdlog::error("Error getting symbol: {}", dlerror());
        dlclose(handle);
        return false;
    }

    // 调用共享库中的函数
    res = func_p(args...);

    // 关闭共享库
    dlclose(handle);
    return true;
#else
// TODO: 其它系统
#endif
}
UTILS_NAMESPACE_END