#ifndef NSW_SOCKET_H
#define NSW_SOCKET_H

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
#    define NSW_AF_LOCAL AF_UNIX
#    define NSW_AF_INET AF_INET
#    define NSW_AF_INET6 AF_INET6

#    define NSW_SOCK_STREAM SOCK_STREAM
#    define NSW_SOCK_DGRAM SOCK_DGRAM
#elif NSW_WINSOCK
#    error "e"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int nsw_socket_t;
    typedef int nsw_address_family_t;
    typedef int nsw_socket_type_t;
    typedef int nsw_socket_protocol_t;

    NSW_EXPORT nsw_socket_t nsw_socket(nsw_address_family_t af,
                                       nsw_socket_type_t type,
                                       nsw_socket_protocol_t protocol);

    NSW_EXPORT nsw_reterr_t nsw_close(nsw_socket_t socket);

    NSW_EXPORT bool nsw_isSocket(nsw_socket_t socket);

#ifdef __cplusplus
}
#endif

#endif