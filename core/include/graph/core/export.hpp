#pragma once

#ifdef graph_core_SHARED_DEFINE
#   ifndef GRAPH_CORE_EXPORT
#       ifdef graph_core_EXPORTS
#           if defined _WIN32 
#               define GRAPH_CORE_EXPORT __declspec(dllexport)
#           elif defined __GNUC__ || defined __clang__
#               define GRAPH_CORE_EXPORT __attribute__((visibility("default")))
#           endif
#       else
#           if defined _WIN32 
#               define GRAPH_CORE_EXPORT __declspec(dllimport)
#           elif defined __GNUC__ || defined __clang__
#               define GRAPH_CORE_EXPORT __attribute__((visibility("default")))
#           endif
#       endif
#   endif
#   ifndef GRAPH_CORE_NO_EXPORT
#       if defined _WIN32 
#           define GRAPH_CORE_NO_EXPORT
#       elif defined __GNUC__ || defined __clang__
#           define GRAPH_CORE_NO_EXPORT __attribute__((visibility("hidden")))
#       endif
#   endif
#else 
#   define GRAPH_CORE_EXPORT
#   define GRAPH_CORE_NO_EXPORT
#endif

#ifndef GRAPH_CORE_DEPRECATED
#   if defined _WIN32 
#       define GRAPH_CORE_DEPRECATED __declspec(deprecated)
#   elif defined __GNUC__ || defined __clang__
#       define GRAPH_CORE_DEPRECATED __attribute__ ((__deprecated__))
#   endif
#endif

#ifndef GRAPH_CORE_DEPRECATED_EXPORT
#  define GRAPH_CORE_DEPRECATED_EXPORT GRAPH_CORE_EXPORT GRAPH_CORE_DEPRECATED
#endif

#ifndef GRAPH_CORE_DEPRECATED_NO_EXPORT
#  define GRAPH_CORE_DEPRECATED_NO_EXPORT GRAPH_CORE_NO_EXPORT GRAPH_CORE_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define GRAPH_CORE_NO_DEPRECATED
#endif
