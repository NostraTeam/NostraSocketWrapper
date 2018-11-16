#include "nostrasocketwrapper/socket.h"

#ifndef NSW_ERROR_H
#    include "nostrasocketwrapper/error.h"
#endif

#ifdef NSW_POSIX
#    include <errno.h>
#    include <netinet/in.h>
#    include <sys/stat.h>
#    include <unistd.h>
#elif defined(NSW_WINSOCK)
#    include <winsock2.h>
#endif

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

    nsw_reterr_t nsw_initialize(void)
    {
#ifdef NSW_POSIX
        /* NO-OP on Unix */
        return 0;
#elif defined(NSW_WINSOCK)
    WSADATA wsdata;

    int result = WSAStartup(MAKEWORD(2, 2), &wsdata);

    if(result != 0)
    {
        nsw_set_error(result);

        return -1;
    }
    else
        return 0;
#endif
    }

    nsw_reterr_t nsw_terminate(void)
    {
#ifdef NSW_POSIX
        /* NO-OP on Unix */
        return 0;
#elif defined(NSW_WINSOCK)

    int err = WSACleanup();

    if(err == NSW_INTERNAL_SOCKET_ERROR)
    {
        nsw_set_error(nsw_internal_get_errno());
        return -1;
    }
    else
        return 0;

#endif
    }

    nsw_socket_t nsw_socket(nsw_address_family_t af, nsw_socket_type_t type, nsw_socket_protocol_t protocol)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

        nsw_socket_t ret = (nsw_socket_t)socket(af, type, protocol);

        if(ret == NSW_INVALID_SOCKET)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return NSW_INVALID_SOCKET;
        }
        return ret;
    }

    nsw_sockaddr_t *nsw_clear_sockaddr(nsw_sockaddr_t *sockaddr)
    {
        memset(sockaddr, 0, sizeof(nsw_sockaddr_t));
        return sockaddr;
    }

    nsw_reterr_t nsw_connect(nsw_socket_t socket, const nsw_sockaddr_t *addr)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

        int err = connect(socket, (struct sockaddr *)addr, sizeof(nsw_sockaddr_t));

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return -1;
        }

        return 0;
    }

    nsw_reterr_t nsw_bind(nsw_socket_t socket, const nsw_sockaddr_t *addr)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

        int err = bind(socket, (struct sockaddr *)addr, sizeof(nsw_sockaddr_t));

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return -1;
        }

        return 0;
    }

    nsw_reterr_t nsw_listen(nsw_socket_t socket, int backlog)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

        int err = listen(socket, backlog);

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return -1;
        }

        return 0;
    }

    nsw_socket_t nsw_accept(nsw_socket_t socket, nsw_sockaddr_t *addr)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

#ifdef NSW_POSIX
        typedef socklen_t nsw_locl_socklen_t;
#elif defined(NSW_WINSOCK)
    typedef int nsw_locl_socklen_t;
#endif

        nsw_locl_socklen_t len = sizeof(nsw_sockaddr_t);
        nsw_socket_t ret       = accept(socket, (struct sockaddr *)addr, &len);

        if(ret == NSW_INVALID_SOCKET)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return NSW_INVALID_SOCKET;
        }

        return ret;
    }

    nsw_ssize_t nsw_send(nsw_socket_t socket, const void *data, size_t len, unsigned int flags)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

#ifdef NSW_POSIX
        typedef size_t nsw_local_lenght_type;
#elif defined(NSW_WINSOCK)
    typedef int nsw_local_lenght_type;
#endif

        int err = send(socket, data, (nsw_local_lenght_type)len, flags);

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return -1;
        }

        return err;
    }

    nsw_ssize_t nsw_recv(nsw_socket_t socket, void *data, size_t len, unsigned int flags)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

#ifdef NSW_POSIX
        typedef size_t nsw_local_lenght_type;
#elif defined(NSW_WINSOCK)
    typedef int nsw_local_lenght_type;
#endif

        int err = recv(socket, data, (nsw_local_lenght_type)len, flags);

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return -1;
        }

        return err;
    }

    nsw_reterr_t nsw_close(nsw_socket_t socket)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#endif

#ifdef NSW_POSIX
        int err = close(socket);
#elif defined(NSW_WINSOCK)
    int err = closesocket(socket);
#endif

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
            nsw_set_error(nsw_internal_get_errno());

#ifdef NSW_RESTORE_ERRNO
            nsw_internal_set_errno(oldErrno);
#endif

            return -1;
        }

        return 0;
    }

    bool nsw_is_socket(nsw_socket_t socket)
    {
#ifdef NSW_POSIX
#    ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = nsw_internal_get_errno();
#    endif

        struct stat statbuf;
        int err = fstat(socket, &statbuf);

        if(err == NSW_INTERNAL_SOCKET_ERROR)
        {
#    ifdef NSW_RESTORE_ERRNO
            nsw_internal_get_errno() = oldErrno;
#    endif
            return false;
        }

        return (bool)(S_ISSOCK(statbuf.st_mode) != 0);
#elif defined(NSW_WINSOCK)
    return false;
#endif
    }

#ifdef __cplusplus
}
#endif
