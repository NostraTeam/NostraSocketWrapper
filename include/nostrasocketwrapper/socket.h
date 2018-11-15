#ifndef NSW_SOCKET_H
#define NSW_SOCKET_H

/**
\file nostrasocketwrapper/socket.h

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0

\brief
A component that provides the functions to enable working with sockets.

\par_example
\code{.cpp}
\todo <EXAMPLE HERE>
\endcode

For a more detailed example, see \link socket.ex.c here\endlink.
*/

/**
\example socket.ex.c

An example that demonstrates the usage of the functionality provided by the socket component.
*/

#ifndef NSW_PLATDECT_H
#    include "nostrasocketwrapper/platdect.h"
#endif

#ifndef NSW_EXPORT_H
#    include "nostrasocketwrapper/export.h"
#endif

#ifndef NSW_ERROR_H
#    include "nostrasocketwrapper/error.h"
#endif

#ifdef NSW_POSIX
#    include <stdbool.h>
#    include <sys/socket.h>
#    include <sys/types.h> //for old BSD
#endif

#ifdef NSW_POSIX
#    define NSW_AF_INET AF_INET
#    define NSW_AF_INET6 AF_INET6

#    define NSW_SOCK_STREAM SOCK_STREAM
#    define NSW_SOCK_DGRAM SOCK_DGRAM
#elif NSW_WINSOCK
#    error "e"
#elif _DOXYGEN_

// Empty definitions for Doxygen; only these need to be documented

/**
\brief
The socket family for communication using IPv4.

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0
*/
#    define NSW_AF_INET

/**
\brief
The socket family for communication using IPv6.

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0
*/
#    define NSW_AF_INET6

/**
\brief
The socket type for communication using TCP/IP.

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0
*/
#    define NSW_SOCK_STREAM

/**
\brief
The socket type for communication using UDP.

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0
*/
#    define NSW_SOCK_DGRAM
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    /**
    \brief
    The type of sockets.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_socket_t;

    /**
    \brief
    The type of an socket family.

    \details
    None.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_address_family_t;

    /**
    \brief
    The type of an socket type.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_socket_type_t;

    /**
    \brief
    The type of a socket protocol.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_socket_protocol_t;

    typedef ssize_t nsw_ssize_t;

    typedef struct sockaddr_in nsw_sockaddr_t;

    nsw_reterr_t nsw_initialize(void);

    nsw_reterr_t nsw_terminate(void);

    /**
    \param af
    The socket family. The passed value must be &isin; {\ilc{NSW_AF_INET}, \ilc{NSW_AF_INET6}}.

    \param type
    The socket type. The passed value must be &isin; {\ilc{NSW_SOCK_STREAM}, \ilc{NSW_SOCK_DGRAM}}.

    \param protocol
    The protocol. Usually, this is \ilc{0}.

    \return
    \ilc{-1} on success, \ilc{0} on success.

    \brief
    Creates a new socket from the passed parameters.

    \details
    On failure, one of the following errors will be set:

    <table class="errorcode_table">
        <tr>
            <td>
                NSW_ERR_ACCESS_DENIED
            </td>
            <td>
                The process does not have the permission to create the socket with the specified type and/or
                protocol.
            </td>
        </tr>
        <tr>
            <td>
                NSW_ERR_FAMILY_NOT_SUPPORTED
            </td>
            <td>
                The system does not support the specified socket family.
            </td>
        </tr>
        <tr>
            <td>
                NSW_ERR_INVALID_PARAMETER
            </td>
            <td>
                Unknown family, type or protocol.
            </td>
        </tr>
        <tr>
            <td>
                NSW_ERR_TOO_MANY_PROCESS_FILES
            </td>
            <td>
                There are too many sockets (or file descriptors in general on Unix systems) opened by the
                process.
            </td>
        </tr>
        <tr>
            <td>
                NSW_ERR_TOO_MANY_SYSTEM_FILES
            </td>
            <td>
                There are too many sockets (or file descriptors in general on Unix systems) opened by the
                system.
            </td>
        </tr>
        <tr>
            <td>
                NSW_OUT_OF_MEMORY
            </td>
            <td>
                The process has run out of memory.
            </td>
        </tr>
        <tr>
            <td>
                EPROTONOSUPPORT
            </td>
            <td>
                Either the type or protocol is not supported.
            </td>
        </tr>
        <tr>
            <td>
                NSW_ERR_UNKNOWN
            </td>
            <td>
                An unknown error occurred.
            </td>
        </tr>
    </table>

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT nsw_socket_t nsw_socket(nsw_address_family_t af,
                                       nsw_socket_type_t type,
                                       nsw_socket_protocol_t protocol);

    nsw_sockaddr_t *nsw_clear_sockaddr(nsw_sockaddr_t *sockaddr);

    nsw_reterr_t nsw_connect(nsw_socket_t socket, const nsw_sockaddr_t *addr);

    nsw_reterr_t nsw_bind(nsw_socket_t socket, const nsw_sockaddr_t *addr);

    nsw_reterr_t nsw_listen(nsw_socket_t socket, int backlog);

    nsw_socket_t nsw_accept(nsw_socket_t socket, nsw_sockaddr_t *addr);

    nsw_ssize_t nsw_send(nsw_socket_t socket, const void *data, size_t len, unsigned int flags);

    nsw_ssize_t nsw_recv(nsw_socket_t socket, void *data, size_t len, unsigned int flags);

    /**
    \param socket
    The socket to close.

    \return
    \ilc{-1} on success, \ilc{0} on success.

    \brief
    Closes a socket that was previously opened by \ilc{nsw_socket()}.

    \details
    On failure, one of the following errors will be set:

    <table class="errorcode_table">
        <tr>
            <td>
                NSW_ERR_INVALID_PARAMETER
            </td>
            <td>
                \ilc{socket} is not a valid file descriptor.
            </td>
        </tr>
        <tr>
            <td>
                NSW_ERR_UNKNOWN
            </td>
            <td>
                An unknown error occurred.
            </td>
        </tr>
    </table>

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT nsw_reterr_t nsw_close(nsw_socket_t socket);

    /**
    \param socket
    The socket to check.

    \return
    \ilc{true}, if \ilc{socket} is a valid one, \ilc{false} if it is not.

    \brief
    Checks wheather a socket is valid and usable by the process.

    \details
    This function will never set an error, instead, if any system call called by this function fails, it will
    be assumed that this is beacause of problems with the socket. Hence, \ilc{false} will be returned in such
    case.

    \note
    If \ilc{NSW_RESTORE_ERRNO} is not defined, \ilc{errno}/\ilc{GetLastError()} may return an error, even if
    \ilc{nsw_get_error()} does not.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT bool nsw_is_socket(nsw_socket_t socket); ///\todo Rename to nsw_is_socket()

#ifdef __cplusplus
}
#endif

#endif
