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
bool call_func(const char *lib_name, const char *func_name, T &res, Args... args)
{
    FuncPtr<T, Args...> func_p;

#ifdef OS_WINDOWS
    // 打开共享库
    HMODULE handle = LoadLibrary(lib_name);
    if (!handle)
    {
        spdlog::error("Failed to load library: ", GetLastError());
        return false;
    }
    // 获取共享库中的函数指针并调用
    func_p = (FuncPtr)GetProcAddress(handle, func_name);
    if (!func_p)
    {
        spdlog::error("Failed to get function pointer: ", dlerror());
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
    void *handle = dlopen(lib_name, RTLD_LAZY);
    if (!handle)
    {
        spdlog::error("Failed to load library: ", dlerror());
        return false;
    }

    // 获取共享库中的函数指针并调用
    func_p = reinterpret_cast<FuncPtr<T, Args...>>(dlsym(handle, func_name));
    if (!func_p)
    {
        spdlog::error("Failed to get function pointer: ", dlerror());
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