#pragma once

#include <unordered_map>

#include "utils.hpp"

#ifdef OS_WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

UTILS_NAMESPACE_BEGIN
template <typename Res, typename... Args>
using FuncPtr = Res (*)(Args...);

class DynamicLibManager
{
public:
    DynamicLibManager() = default;
    ~DynamicLibManager()
    {
        for (auto& lib : m_libs)
        {
#ifdef OS_WINDOWS
            FreeLibrary(reinterpret_cast<HMODULE>(lib.second));
#else
            dlclose(lib.second);
#endif
        }
    }

    bool load_library(const std::string& lib_name)
    {
        if (m_libs.find(lib_name) != m_libs.end())
        {
            return true;
        }
#ifdef OS_WINDOWS
        HMODULE handle = LoadLibraryA(lib_name.c_str());
        if (!handle)
        {
            spdlog::error("Error opening library: {}", GetLastError());
            return false;
        }
        m_libs[lib_name] = reinterpret_cast<void*>(handle);
#else
        void* handle = dlopen(lib_name.c_str(), RTLD_LAZY);
        if (!handle)
        {
            spdlog::error("Error opening library: {}", dlerror());
            return false;
        }
        m_libs[lib_name] = handle;
#endif
        return true;
    }

    template <typename T, typename... Args>
    bool call_func(const std::string& lib_name, const std::string& func_name, T& res, Args... args)
    {
        if (m_libs.find(lib_name) == m_libs.end())
        {
            if (!load_library(lib_name))
            {
                return false;
            }
        }

        FuncPtr<T, Args...> func_p;
        void* handle = m_libs[lib_name];
#ifdef OS_WINDOWS
        func_p = reinterpret_cast<FuncPtr<T, Args...>>(GetProcAddress(static_cast<HMODULE>(handle), func_name.c_str()));
        if (!func_p)
        {
            spdlog::error("Error getting symbol: {}", GetLastError());
            return false;
        }
#else
        func_p = reinterpret_cast<FuncPtr<T, Args...>>(dlsym(handle, func_name.c_str()));
        if (!func_p)
        {
            spdlog::error("Error getting symbol: {}", dlerror());
            return false;
        }
#endif
        res = func_p(args...);
        return true;
    }

private:
    std::unordered_map<std::string, void*> m_libs;
};
UTILS_NAMESPACE_END
