#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#ifndef UTILS_NAMESPACE_BEGIN
#define UTILS_NAMESPACE_BEGIN \
    namespace utils           \
    {
#define UTILS_NAMESPACE_END }
#endif

/* Windows */
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define OS_WINDOWS 1

/* Linux */
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define OS_LINUX 1

/* MAC */
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
#define OS_MAC 1

/* Unknown OS */
#else
#define OS_UNKNOWN 4
#endif // OS detect

#ifndef EXPORT
#ifdef OS_LINUX
#define EXPORT extern "C"
#elif defined(OS_WINDOWS)
#define EXPORT extern "C" __declspec(dllexport)
#else
/*OS_UNKNOWN*/
#endif
#endif

UTILS_NAMESPACE_BEGIN
template <typename T>
int find(const std::vector<T> &vec, const T &target)
{
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it == vec.end())
    {
        return -1;
    }

    return std::distance(vec.begin(), it);
}

template <typename T, typename FUNC>
int find_if(const std::vector<T> &vec, FUNC func)
{
    auto it = std::find_if(vec.begin(), vec.end(), func);
    if (it == vec.end())
    {
        return -1;
    }

    return std::distance(vec.begin(), it);
}

template <typename T, typename FUNC>
std::vector<T> get_if(const std::vector<T> &source, FUNC func)
{
    std::vector<T> res;
    std::copy_if(source.begin(), source.end(), std::back_inserter(res), func);
    return res;
}

template <typename T, typename FUNC>
void copy_if(const std::vector<T> &source, std::vector<T> &dest, FUNC func)
{
    std::copy_if(source.begin(), source.end(), std::back_inserter(dest), func);
}

template <typename K, typename V>
bool find(const std::map<K, V> d, K key)
{
    return d.find(key) != d.end();
}

inline bool get_files(const std::string &path, const std::string &suffix, std::vector<std::string> &files)
{
    if (!std::filesystem::exists(path))
    {
        spdlog::error("path not exists: ", path);
        return false;
    }

    for (auto &&file : std::filesystem::directory_iterator(path))
    {
        if (file.path().extension() == suffix)
        {
            files.push_back(file.path().string());
        }
    }
    return true;
}
UTILS_NAMESPACE_END