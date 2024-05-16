#pragma once

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

#ifndef API
#ifdef OS_WINDOWS
#define API extern "C" __declspec(dllexport)
#elif defined(OS_LINUX)
#define API extern "C"
#else
/*OS_UNKNOWN*/
#endif
#endif

UTILS_NAMESPACE_BEGIN

UTILS_NAMESPACE_END