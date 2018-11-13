#ifndef NSW_PLATDECT_H
#define NSW_PLATDECT_H

#if defined(NSW_LIB_OVERRIDE_POSIX) && defined(NSW_LIB_OVERRIDE_WINSOCK)
#    error "NSW_LIB_OVERRIDE_POSIX and NSW_LIB_OVERRIDE_WINSOCK can not be defined at the same time."
#endif

#if defined(NSW_LIB_OVERRIDE_POSIX)
#    define NSW_POSIX
#elif defined(NSW_LIB_OVERRIDE_WINSOCK)
#    define NSW_WINSOCK
#endif

#if !defined(NSW_WINSOCK) && !defined(NSW_POSIX)
#    if defined(__unix__)
#        define NSW_POSIX
#    elif defined _WIN32
#        define NSW_WINSOCK
#    else
#        error "Operating system is not supported."
#    endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif