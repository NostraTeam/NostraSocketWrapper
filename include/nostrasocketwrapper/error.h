#ifndef NSW_ERROR_H
#define NSW_ERROR_H

/**
\file nostrasocketwrapper/error.h

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0

\brief
A component that provides the error handling system of NSW.

\details
None of the error codes (the macros \ilc{NSW_E*}) in this component are documented, because they may have
slightly different meanings in different contexts. However, the functions in which the errors are set will
have information on when certain errors will be set.

Additionally, each error code consists of three parts:
<table>
    <tr>
        <td>
            The code macro.
        </td>
        <td>
            The code macro holds the actual, numeric error code.
        </td>
    </tr>
    <tr>
        <td>
            The name macro.
        </td>
        <td>
            The name macro holds the name of the code macro as a string. E.g.: The name macro if
            \ilc{NSW_ESUCCESS} expands to \ilc{"NSW_ESUCCESS"}. These are used by nsw_errorName().
        </td>
    </tr>
    <tr>
        <td>
            The text macro.
        </td>
        <td>
            The text macro holds a short text that describes the error. These are used by nsw_errorText().
        </td>
    </tr>
</table>

\par_example
\code{.cpp}
\todo <EXAMPLE HERE>
\endcode

For a more detailed example, see \link error.ex.c here\endlink.
*/

/**
\example error.ex.c

An example that demonstrates the usage of the functionality provided by the error component.
*/

#ifndef NSW_EXPORT_H
#    include "nostrasocketwrapper/export.h"
#endif

#ifndef NSW_PLATDECT_H
#    include "nostrasocketwrapper/platdect.h"
#endif

#ifdef NSW_POSIX
#    include <errno.h>
#elif defined(NSW_WINSOCK)
#    include <WinSock2.h> /** \todo remove this include */
#endif

/* #define NSW_ESUCCESS 0 */
/*#define NSW_ESUCCESS_NAME "NSW_ESUCCESS" */
/*#define NSW_ESUCCESS_TEXT "No error happened." */

/* #define NSW_EUNKNOWN -1 */
/* #define NSW_EUNKNOWN_NAME "NSW_EUNKNOWN" */
/* #define NSW_EUNKNOWN_TEXT "An unknown error happened." */

/*
#ifdef NSW_POSIX
#    define NSW_EACCES EACCES
#    define NSW_EADDRINUSE EADDRINUSE
#    define NSW_EADDRNOTAVAIL EADDRNOTAVAIL
#    define NSW_EAFNOSUPPORT EAFNOSUPPORT
#    define NSW_EAGAIN EAGAIN
#    define NSW_EALREADY EALREADY
#    define NSW_EBADF EBADF
#    define NSW_ECONNABORTED ECONNABORTED
#    define NSW_ECONNREFUSED ECONNREFUSED
#    define NSW_ECONNRESET ECONNRESET
#    define NSW_EDESTADDRREQ EDESTADDRREQ
#    define NSW_EFAULT EFAULT
#    define NSW_EINPROGRESS EINPROGRESS
#    define NSW_EINTR EINTR
#    define NSW_EINVAL EINVAL
#    define NSW_EISCONN EISCONN
#    define NSW_ELOOP ELOOP
#    define NSW_EMFILE EMFILE
#    define NSW_EMSGSIZE EMSGSIZE
#    define NSW_ENAMETOOLONG ENAMETOOLONG
#    define NSW_ENETUNREACH ENETUNREACH
#    define NSW_ENFILE ENFILE
#    define NSW_ENOBUFS ENOBUFS
#    define NSW_ENOENT ENOENT
#    define NSW_ENOMEM ENOMEM
#    define NSW_ENOTCONN ENOTCONN
#    define NSW_ENOTDIR ENOTDIR
#    define NSW_ENOTSOCK ENOTSOCK
#    define NSW_EOPNOTSUPP EOPNOTSUPP
#    define NSW_EPERM EPERM
#    define NSW_EPIPE EPIPE
#    define NSW_EPROTO EPROTO
#    define NSW_EPROTONOSUPPORT EPROTONOSUPPORT
#    define NSW_EPROTOTYPE EPROTOTYPE
#    define NSW_EROFS EROFS
#    define NSW_ETIMEDOUT ETIMEDOUT
#    define NSW_EWOULDBLOCK EWOULDBLOCK
#    define NSW_ESYSNOTREADY -1
#    define NSW_EVERNOTSUPPORTED -2
#    define NSW_EPROCLIM -3
#    define NSW_ENNOTINITIALIZED -4
#    define NSW_ENETDOWN -5
#elif defined(NSW_WINSOCK)
#    define NSW_EACCES WSAEACCES
#    define NSW_EADDRINUSE WSAEADDRINUSE
#    define NSW_EADDRNOTAVAIL WSAEADDRNOTAVAIL
#    define NSW_EAFNOSUPPORT WSAEAFNOSUPPORT
#    define NSW_EAGAIN -1
#    define NSW_EALREADY WSAEALREADY
#    define NSW_EBADF WSAEBADF
#    define NSW_ECONNABORTED WSAECONNABORTED
#    define NSW_ECONNREFUSED WSAECONNREFUSED
#    define NSW_ECONNRESET WSAECONNRESET
#    define NSW_EDESTADDRREQ WSAEDESTADDRREQ
#    define NSW_EFAULT WSAEFAULT
#    define NSW_EINPROGRESS WSAEINPROGRESS
#    define NSW_EINTR WSAEINTR
#    define NSW_EINVAL WSAEINVAL
#    define NSW_EISCONN WSAEISCONN
#    define NSW_ELOOP WSAELOOP
#    define NSW_EMFILE WSAEMFILE
#    define NSW_EMSGSIZE WSAEMSGSIZE
#    define NSW_ENAMETOOLONG WSAENAMETOOLONG
#    define NSW_ENETUNREACH WSAENETUNREACH
#    define NSW_ENFILE -2
#    define NSW_ENOBUFS WSAENOBUFS
#    define NSW_ENOENT -3
#    define NSW_ENOMEM -4
#    define NSW_ENOTCONN WSAENOTCONN
#    define NSW_ENOTDIR -5
#    define NSW_ENOTSOCK WSAENOTSOCK
#    define NSW_EOPNOTSUPP WSAEOPNOTSUPP
#    define NSW_EPERM -6
#    define NSW_EPIPE -7
#    define NSW_EPROTO -8
#    define NSW_EPROTONOSUPPORT -9
#    define NSW_EPROTOTYPE WSAEPROTOTYPE
#    define NSW_EROFS -10
#    define NSW_ETIMEDOUT WSAETIMEDOUT
#    define NSW_EWOULDBLOCK WSAEWOULDBLOCK
#    define NSW_ESYSNOTREADY WSASYSNOTREADY
#    define NSW_EVERNOTSUPPORTED WSAVERNOTSUPPORTED
#    define NSW_EPROCLIM WSAEPROCLIM
#    define NSW_ENNOTINITIALIZED WSANOTINITIALISED
#    define NSW_ENETDOWN WSAENETDOWN
#endif
*/

#ifdef NSW_POSIX
#    define NSW_INTERNAL_SOCKET_ERROR -1
#elif defined(NSW_WINSOCK)
#    define NSW_INTERNAL_SOCKET_ERROR SOCKET_ERROR
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        NSW_ESUCCESS,
        NSW_EUNKNOWN,
        NSW_ENOTINITIALIZED,
        NSW_EAFNOSUPPORT,
        NSW_EPROTONOSUPPORT,
        NSW_ENOBUFS,
        NSW_EMFILE,
        NSW_EACCES,
        NSW_EINVAL,
        NSW_ENETDOWN,
        NSW_EINPROGRESS,
        NSW_EINVALIDPROVIDER,
        NSW_EINVALIDPROCTABLE,
        NSW_EPROVIDERFAILEDINIT,
        NSW_ENOTSOCK,
        NSW_EINTR,
        NSW_EADDRINUSE,
        NSW_EOPNOTSUPP
    } nsw_error_t;

    /**
    \brief
    The type that is used for errors.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    // typedef int nsw_error_t;

    typedef int nsw_internal_errno_t;

    /**
    \brief
    The type that is used when returning a success or error state.

    \details
    When this type is the return type of a function, the returned value will either be \ilc{0} when the
    function succeeded or \ilc{-1} when it failed.

    \warning
    The values returned using this type are not error codes. For error codes, the type \ilc{new_error_t} is
    used.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_reterr_t;

    /**
    \return
    The current error code.

    \brief
    Returns the current error code.

    \details
    Since the error codes are specific to each thread, the result of this function may vary from thread to
    thread.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT extern nsw_error_t nsw_get_error(void);

    /**
    \param error
    The new error code.

    \brief
    Sets the error code of the calling thread.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT extern void nsw_set_error(nsw_error_t error);

    /** \todo Mark as NSW_NO_EXPORT (currently, with NSW_NO_EXPORT tests don't work) */

    NSW_EXPORT extern nsw_internal_errno_t nsw_internal_get_errno();

    NSW_EXPORT extern void nsw_internal_set_errno(nsw_internal_errno_t error);

    NSW_EXPORT nsw_error_t nsw_internal_map_error_socket(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_connect(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_bind(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_listen(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_accept(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_send(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_recv(nsw_internal_errno_t error);
    NSW_EXPORT nsw_error_t nsw_internal_map_error_close(nsw_internal_errno_t error);

    /* <- WARNING: not a doxygen comment
    \param error
    The error code to get the name of.

    \brief
    Returns the name of \ilc{error} as a string.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    /* NSW_EXPORT const char *nsw_errorName(nsw_error_t error); */

    /* <- WARNING: not a doxygen comment
    \param error
    The error code to get the description text of.

    \brief
    Returns a short description text for \ilc{error}.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    /* NSW_EXPORT const char *nsw_errorText(nsw_error_t error); */

#ifdef __cplusplus
}
#endif

#endif
