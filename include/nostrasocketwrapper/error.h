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

#include <errno.h>

#define NSW_ESUCCESS 0
//#define NSW_ESUCCESS_NAME "NSW_ESUCCESS"
//#define NSW_ESUCCESS_TEXT "No error happened."

#define NSW_EUNKNOWN -1
//#define NSW_EUNKNOWN_NAME "NSW_EUNKNOWN"
//#define NSW_EUNKNOWN_TEXT "An unknown error happened."

#ifdef NSW_POSIX
#    define NSW_EACCES EACCES
#    define NSW_EADDRINUSE EADDRINUSE
#    define NSW_EADDRNOTAVAIL EADDRNOTAVAIL
#    define NSW_EAFNOSUPPORT EAFNOSUPPORT
#    define NSW_EAGAIN EAGAIN
#    define NSW_EALREADY EALREADY
#    define NSW_EBADF EBADF
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
#    define NSW_EPROTONOSUPPORT EPROTONOSUPPOR
#    define NSW_EPROTOTYPE EPROTOTYPE
#    define NSW_EROFS EROFS
#    define NSW_ETIMEDOUT ETIMEDOUT
#    define NSW_EWOULDBLOCK EWOULDBLOCK
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    \brief
    The type that is used for errors.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_error_t;

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
    extern nsw_error_t nsw_get_error(void);

    /**
    \param error
    The new error code.

    \brief
    Sets the error code of the calling thread.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    extern void nsw_set_error(nsw_error_t error);

    /* // <- WARNING: not a doxygen comment
    \param error
    The error code to get the name of.

    \brief
    Returns the name of \ilc{error} as a string.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    // NSW_EXPORT const char *nsw_errorName(nsw_error_t error);

    /* // <- WARNING: not a doxygen comment
    \param error
    The error code to get the description text of.

    \brief
    Returns a short description text for \ilc{error}.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    // NSW_EXPORT const char *nsw_errorText(nsw_error_t error);

#ifdef __cplusplus
}
#endif

#endif
