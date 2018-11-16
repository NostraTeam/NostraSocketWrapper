#include "nostrasocketwrapper/error.h"

#include <string.h> /* size_t */

#ifdef NSW_POSIX
#    define NSW_INTERNAL_THREAD_LOCAL __thread
#elif defined(NSW_WINSOCK)
#    define NSW_INTERNAL_THREAD_LOCAL __declspec(thread)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    /*
    The variable that stores the current error code per thread.
    */
    NSW_INTERNAL_THREAD_LOCAL nsw_error_t nsw_internal_error = NSW_ESUCCESS;

    inline nsw_error_t nsw_get_error(void)
    {
        return nsw_internal_error;
    }

    inline void nsw_set_error(nsw_error_t error)
    {
        nsw_internal_error = error;
    }

    inline nsw_internal_errno_t nsw_internal_get_errno()
    {
#ifdef NSW_POSIX
        return (nsw_error_t)errno;
#elif defined(NSW_WINSOCK)
    return WSAGetLastError();
#endif
    }

    inline void nsw_internal_set_errno(nsw_internal_errno_t error)
    {
#ifdef NSW_POSIX
        errno = error;
#elif defined(NSW_WINSOCK)
    WSASetLastError(error);
#endif
    }

    nsw_error_t nsw_internal_map_error_socket(nsw_internal_errno_t error)
    {
#ifdef NSW_POSIX /* mappings for POSIX */
        switch(error)
        {
            case EAFNOSUPPORT:
                return NSW_EAFNOSUPPORT;
            case EPROTONOSUPPORT:
                return NSW_EPROTONOSUPPORT;
            case ENOBUFS:
                return NSW_ENOBUFS;
            case ENOMEM:
                return NSW_ENOBUFS;
            case EMFILE:
                return NSW_EMFILE;
            case ENFILE:
                return NSW_EMFILE;
            case EACCES:
                return NSW_EACCES;
            case EINVAL:
                return NSW_EINVAL;
            default:
                return NSW_EUNKNOWN;
        }
#elif defined(NSW_WINSOCK) /* mappings for Winsock */
    switch(error)
    {
        case WSANOTINITIALISED:
            return NSW_ENOTINITIALIZED;
        case WSAEAFNOSUPPORT:
            return NSW_EAFNOSUPPORT;
        case WSAEPROTONOSUPPORT:
            return NSW_EPROTONOSUPPORT;
        case WSAEPROTOTYPE:
            return NSW_EPROTOTYPE;
        case WSAENOBUFS:
            return NSW_ENOBUFS;
        case WSAEMFILE:
            return NSW_EMFILE;
        case WSAEINVAL:
            return NSW_EINVAL;
        case WSAESOCKTNOSUPPORT:
            return NSW_ESOCKTNOSUPPORT;
        case WSAENETDOWN:
            return NSW_ENETDOWN;
        case WSAEINPROGRESS:
            return NSW_EINPROGRESS;
        case WSAEINVALIDPROVIDER:
            return NSW_EINVALIDPROVIDER;
        case WSAEINVALIDPROCTABLE:
            return NSW_EINVALIDPROCTABLE;
        case WSAEPROVIDERFAILEDINIT:
            return NSW_EPROVIDERFAILEDINIT;
        default:
            return NSW_EUNKNOWN;
    }
#endif
    }

    nsw_error_t nsw_internal_map_error_connect(nsw_internal_errno_t error)
    {
        return NSW_EUNKNOWN;
    }

    nsw_error_t nsw_internal_map_error_bind(nsw_internal_errno_t error)
    {
        return NSW_EUNKNOWN;
    }

    nsw_error_t nsw_internal_map_error_listen(nsw_internal_errno_t error)
    {
#ifdef NSW_POSIX /* mappings for POSIX */
        switch(error)
        {
            case EBADF:
                return NSW_ENOTSOCK;
            case ENOTSOCK:
                return NSW_ENOTSOCK;
            case EADDRINUSE:
                return NSW_EADDRINUSE;
            case EOPNOTSUPP:
                return NSW_EOPNOTSUPP;
            default:
                return NSW_EUNKNOWN;
        }
#elif defined(NSW_WINSOCK) /* mappings for Winsock */
    switch(error)
    {
        case WSANOTINITIALISED:
            return NSW_ENOTINITIALIZED;
        case WSAENETDOWN:
            return NSW_ENETDOWN;
        case WSAEINPROGRESS:
            return NSW_EINPROGRESS;
        case WSAEADDRINUSE:
            return NSW_EADDRINUSE;
        case WSAENOTSOCK:
            return NSW_ENOTSOCK;
        case WSAEOPNOTSUPP:
            return NSW_EOPNOTSUPP;
        case WSAEINVAL:
            return NSW_EINVAL;
        case WSAEISCONN:
            return NSW_EISCONN;
        case WSAEMFILE:
            return NSW_EMFILE;
        case WSAENOBUFS:
            return NSW_ENOBUFS;
        default:
            return NSW_EUNKNOWN;
    }
#endif
    }

    nsw_error_t nsw_internal_map_error_accept(nsw_internal_errno_t error)
    {
        return NSW_EUNKNOWN;
    }

    nsw_error_t nsw_internal_map_error_send(nsw_internal_errno_t error)
    {
        return NSW_EUNKNOWN;
    }

    nsw_error_t nsw_internal_map_error_recv(nsw_internal_errno_t error)
    {
        return NSW_EUNKNOWN;
    }

    nsw_error_t nsw_internal_map_error_close(nsw_internal_errno_t error)
    {
#ifdef NSW_POSIX /* mappings for POSIX */
        switch(error)
        {
            case EBADF:
                return NSW_ENOTSOCK;
            case EPROTONOSUPPORT:
                return NSW_EPROTONOSUPPORT;
            case EINTR:
                return NSW_EINTR;
            case ENOSPC:
                return NSW_EUNKNOWN;
            case EDQUOT:
                return NSW_EUNKNOWN;
            case EIO:
                return NSW_EUNKNOWN;
            default:
                return NSW_EUNKNOWN;
        }
#elif defined(NSW_WINSOCK) /* mappings for Winsock */
    switch(error)
    {
        case WSANOTINITIALISED:
            return NSW_ENOTINITIALIZED;
        case WSAENETDOWN:
            return NSW_ENETDOWN;
        case WSAEINPROGRESS:
            return NSW_EINPROGRESS;
        case WSAENOTSOCK:
            return NSW_ENOTSOCK;
        case WSAEINTR:
            return NSW_EINTR;
        case WSAEWOULDBLOCK:
            return NSW_EWOULDBLOCK;
        default:
            return NSW_EUNKNOWN;
    }
#endif
    }

/*
    const char *nsw_errorName(nsw_error_t error)
    {
        switch(error)
        {
            case NSW_ERR_SUCCESS:
                return NSW_ERR_SUCCESS_NAME;

            case NSW_ERR_UNKNOWN:
                return NSW_ERR_UNKNOWN_NAME;

            case NSW_ERR_INVALID_PARAMETER:
                return NSW_ERR_INVALID_PARAMETER_NAME;

            case NSW_ERR_ACCESS_DENIED:
                return NSW_ERR_ACCESS_DENIED_NAME;

            case NSW_ERR_FAMILY_NOT_SUPPORTED:
                return NSW_ERR_FAMILY_NOT_SUPPORTED_NAME;

            case NSW_ERR_TOO_MANY_PROCESS_FILES:
                return NSW_ERR_TOO_MANY_PROCESS_FILES_NAME;

            case NSW_ERR_TOO_MANY_SYSTEM_FILES:
                return NSW_ERR_TOO_MANY_SYSTEM_FILES_NAME;

            case NSW_OUT_OF_MEMORY:
                return NSW_OUT_OF_MEMORY_NAME;

            case NSW_ERR_UNSUPPORTED_PROTOCOL:
                return NSW_ERR_UNSUPPORTED_PROTOCOL_NAME;

            default:
                nsw_set_error(NSW_ERR_INVALID_PARAMETER);
                return NSW_INTERNAL_ERR_UNKNOWN_ERROR_CODE_NAME;
        }
    }

    const char *nsw_errorText(nsw_error_t error)
    {
        switch(error)
        {
            case NSW_ERR_SUCCESS:
                return NSW_ERR_SUCCESS_TEXT;

            case NSW_ERR_UNKNOWN:
                return NSW_ERR_UNKNOWN_TEXT;

            case NSW_ERR_INVALID_PARAMETER:
                return NSW_ERR_INVALID_PARAMETER_TEXT;

            case NSW_ERR_ACCESS_DENIED:
                return NSW_ERR_ACCESS_DENIED_TEXT;

            case NSW_ERR_FAMILY_NOT_SUPPORTED:
                return NSW_ERR_FAMILY_NOT_SUPPORTED_TEXT;

            case NSW_ERR_TOO_MANY_PROCESS_FILES:
                return NSW_ERR_TOO_MANY_PROCESS_FILES_TEXT;

            case NSW_ERR_TOO_MANY_SYSTEM_FILES:
                return NSW_ERR_TOO_MANY_SYSTEM_FILES_TEXT;

            case NSW_OUT_OF_MEMORY:
                return NSW_OUT_OF_MEMORY_TEXT;

            case NSW_ERR_UNSUPPORTED_PROTOCOL:
                return NSW_ERR_UNSUPPORTED_PROTOCOL_TEXT;

            default:
                nsw_set_error(NSW_ERR_INVALID_PARAMETER);
                return NSW_INTERNAL_ERR_UNKNOWN_ERROR_CODE_TEXT;
        }
    }
*/
#ifdef __cplusplus
}
#endif
